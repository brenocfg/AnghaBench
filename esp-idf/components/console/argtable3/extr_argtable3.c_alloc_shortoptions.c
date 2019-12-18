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
struct arg_hdr {int flag; char* shortopts; } ;

/* Variables and functions */
 int ARG_HASOPTVALUE ; 
 int ARG_HASVALUE ; 
 int ARG_TERMINATOR ; 
 char* malloc (size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static
char * alloc_shortoptions(struct arg_hdr * *table)
{
    char *result;
    size_t len = 2;
    int tabindex;

    /* determine the total number of option chars required */
    for(tabindex = 0; !(table[tabindex]->flag & ARG_TERMINATOR); tabindex++)
    {
        struct arg_hdr *hdr = table[tabindex];
        len += 3 * (hdr->shortopts ? strlen(hdr->shortopts) : 0);
    }

    result = malloc(len);
    if (result)
    {
        char *res = result;

        /* add a leading ':' so getopt return codes distinguish    */
        /* unrecognised option and options missing argument values */
        *res++ = ':';

        for(tabindex = 0; !(table[tabindex]->flag & ARG_TERMINATOR); tabindex++)
        {
            struct arg_hdr *hdr = table[tabindex];
            const char *shortopts = hdr->shortopts;
            while(shortopts && *shortopts)
            {
                *res++ = *shortopts++;
                if (hdr->flag & ARG_HASVALUE)
                    *res++ = ':';
                if (hdr->flag & ARG_HASOPTVALUE)
                    *res++ = ':';
            }
        }
        /* null terminate the string */
        *res = 0;
    }

    /*printf("alloc_shortoptions() returns \"%s\"\n",(result?result:"NULL"));*/
    return result;
}