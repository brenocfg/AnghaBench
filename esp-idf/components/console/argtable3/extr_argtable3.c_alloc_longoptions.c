#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct option {char* name; int val; int has_arg; scalar_t__* flag; } ;
struct longoptions {int noptions; struct option* options; scalar_t__ getoptval; } ;
struct arg_hdr {int flag; char* longopts; } ;

/* Variables and functions */
 int ARG_HASOPTVALUE ; 
 int ARG_HASVALUE ; 
 int ARG_TERMINATOR ; 
 scalar_t__ malloc (size_t) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static
struct longoptions * alloc_longoptions(struct arg_hdr * *table)
{
    struct longoptions *result;
    size_t nbytes;
    int noptions = 1;
    size_t longoptlen = 0;
    int tabindex;

    /*
     * Determine the total number of option structs required
     * by counting the number of comma separated long options
     * in all table entries and return the count in noptions.
     * note: noptions starts at 1 not 0 because we getoptlong
     * requires a NULL option entry to terminate the option array.
     * While we are at it, count the number of chars required
     * to store private copies of all the longoption strings
     * and return that count in logoptlen.
     */
    tabindex = 0;
    do
    {
        const char *longopts = table[tabindex]->longopts;
        longoptlen += (longopts ? strlen(longopts) : 0) + 1;
        while (longopts)
        {
            noptions++;
            longopts = strchr(longopts + 1, ',');
        }
    } while(!(table[tabindex++]->flag & ARG_TERMINATOR));
    /*printf("%d long options consuming %d chars in total\n",noptions,longoptlen);*/


    /* allocate storage for return data structure as: */
    /* (struct longoptions) + (struct options)[noptions] + char[longoptlen] */
    nbytes = sizeof(struct longoptions)
             + sizeof(struct option) * noptions
             + longoptlen;
    result = (struct longoptions *)malloc(nbytes);
    if (result)
    {
        int option_index = 0;
        char *store;

        result->getoptval = 0;
        result->noptions = noptions;
        result->options = (struct option *)(result + 1);
        store = (char *)(result->options + noptions);

        for(tabindex = 0; !(table[tabindex]->flag & ARG_TERMINATOR); tabindex++)
        {
            const char *longopts = table[tabindex]->longopts;

            while(longopts && *longopts)
            {
                char *storestart = store;

                /* copy progressive longopt strings into the store */
                while (*longopts != 0 && *longopts != ',')
                    *store++ = *longopts++;
                *store++ = 0;
                if (*longopts == ',')
                    longopts++;
                /*fprintf(stderr,"storestart=\"%s\"\n",storestart);*/

                result->options[option_index].name    = storestart;
                result->options[option_index].flag    = &(result->getoptval);
                result->options[option_index].val     = tabindex;
                if (table[tabindex]->flag & ARG_HASOPTVALUE)
                    result->options[option_index].has_arg = 2;
                else if (table[tabindex]->flag & ARG_HASVALUE)
                    result->options[option_index].has_arg = 1;
                else
                    result->options[option_index].has_arg = 0;

                option_index++;
            }
        }
        /* terminate the options array with a zero-filled entry */
        result->options[option_index].name    = 0;
        result->options[option_index].has_arg = 0;
        result->options[option_index].flag    = 0;
        result->options[option_index].val     = 0;
    }

    /*dump_longoptions(result);*/
    return result;
}