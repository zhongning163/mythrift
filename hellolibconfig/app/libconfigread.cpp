/**
 * @file       example1.cpp
 * @brief      /mythrift/hellolibconfig/app/example1.cpp
 *
 * @date       Sep 14, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <libconfig.h++>

using namespace std;
using namespace libconfig;

// This example reads the configuration file 'example.cfg' and displays
// some of its contents.

int main(int argc, char **argv)
{
    Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("../../hellolibconfig/data/example.cfg");
    } catch (const FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return (EXIT_FAILURE);
    } catch (const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return (EXIT_FAILURE);
    }

    // Get the store name.
    try
    {
        string name = cfg.lookup("name");
        cout << "Store name: " << name << endl << endl;
    } catch (const SettingNotFoundException &nfex)
    {
        cerr << "No 'name' setting in configuration file." << endl;
    }
    const Setting& root = cfg.getRoot();

    // Output a list of all books in the inventory.
    try
    {
        const Setting &books = root["inventory"]["books"];
        int count = books.getLength();
        cout << setw(30) << left << "TITLE" << " " << setw(30) << left << "AUTHOR" << " " << setw(6) << left << "PRICE"
                << " " << "QTY" << endl;
        for (int i = 0; i < count; ++i)
        {
            const Setting &book = books[i];
            // Only output the record if all of the expected fields are present.
            string title, author;
            double price;
            int qty;
            if (!(book.lookupValue("title", title) && book.lookupValue("author", author)
                    && book.lookupValue("price", price) && book.lookupValue("qty", qty)))
                continue;
            cout << setw(30) << left << title << " " << setw(30) << left << author << " " << '$' << setw(6) << right
                    << price << " " << qty << endl;
        }
        cout << endl;
    } catch (const SettingNotFoundException &nfex)
    {
        // Ignore.
    }

    // Output a list of all books in the inventory.
    try
    {
        const Setting &movies = root["inventory"]["movies"];
        int count = movies.getLength();
        cout << setw(30) << left << "TITLE" << " " << setw(10) << left << "MEDIA" << " " << setw(6) << left << "PRICE"
                << " " << "QTY" << endl;
        for (int i = 0; i < count; ++i)
        {
            const Setting &movie = movies[i];

            // Only output the record if all of the expected fields are present.
            string title, media;
            double price;
            int qty;
            if (!(movie.lookupValue("title", title) && movie.lookupValue("media", media)
                    && movie.lookupValue("price", price) && movie.lookupValue("qty", qty)))
                continue;
            cout << setw(30) << left << title << " " << setw(10) << left << media << " " << '$' << setw(6) << right
                    << price << " " << qty << endl;
        }
        cout << endl;
    } catch (const SettingNotFoundException &nfex)
    {
        // Ignore.
    }
    return (EXIT_SUCCESS);
}

