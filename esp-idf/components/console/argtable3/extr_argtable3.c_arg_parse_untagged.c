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
struct arg_hdr {int flag; int (* scanfn ) (void*,char*) ;void* parent; scalar_t__ shortopts; scalar_t__ longopts; } ;
typedef  void arg_end ;

/* Variables and functions */
 int ARG_ENOMATCH ; 
 int ARG_TERMINATOR ; 
 int /*<<< orphan*/  arg_register_error (void*,void*,int,char const*) ; 
 int optind ; 
 int stub1 (void*,char*) ; 

__attribute__((used)) static
void arg_parse_untagged(int argc,
                        char * *argv,
                        struct arg_hdr * *table,
                        struct arg_end *endtable)
{
    int tabindex = 0;
    int errorlast = 0;
    const char *optarglast = NULL;
    void *parentlast = NULL;

    /*printf("arg_parse_untagged(%d,%p,%p,%p)\n",argc,argv,table,endtable);*/
    while (!(table[tabindex]->flag & ARG_TERMINATOR))
    {
        void *parent;
        int errorcode;

        /* if we have exhausted our argv[optind] entries then we have finished */
        if (optind >= argc)
        {
            /*printf("arg_parse_untagged(): argv[] exhausted\n");*/
            return;
        }

        /* skip table entries with non-null long or short options (they are not untagged entries) */
        if (table[tabindex]->longopts || table[tabindex]->shortopts)
        {
            /*printf("arg_parse_untagged(): skipping argtable[%d] (tagged argument)\n",tabindex);*/
            tabindex++;
            continue;
        }

        /* skip table entries with NULL scanfn */
        if (!(table[tabindex]->scanfn))
        {
            /*printf("arg_parse_untagged(): skipping argtable[%d] (NULL scanfn)\n",tabindex);*/
            tabindex++;
            continue;
        }

        /* attempt to scan the current argv[optind] with the current     */
        /* table[tabindex] entry. If it succeeds then keep it, otherwise */
        /* try again with the next table[] entry.                        */
        parent = table[tabindex]->parent;
        errorcode = table[tabindex]->scanfn(parent, argv[optind]);
        if (errorcode == 0)
        {
            /* success, move onto next argv[optind] but stay with same table[tabindex] */
            /*printf("arg_parse_untagged(): argtable[%d] successfully matched\n",tabindex);*/
            optind++;

            /* clear the last tentative error */
            errorlast = 0;
        }
        else
        {
            /* failure, try same argv[optind] with next table[tabindex] entry */
            /*printf("arg_parse_untagged(): argtable[%d] failed match\n",tabindex);*/
            tabindex++;

            /* remember this as a tentative error we may wish to reinstate later */
            errorlast = errorcode;
            optarglast = argv[optind];
            parentlast = parent;
        }

    }

    /* if a tenative error still remains at this point then register it as a proper error */
    if (errorlast)
    {
        arg_register_error(endtable, parentlast, errorlast, optarglast);
        optind++;
    }

    /* only get here when not all argv[] entries were consumed */
    /* register an error for each unused argv[] entry */
    while (optind < argc)
    {
        /*printf("arg_parse_untagged(): argv[%d]=\"%s\" not consumed\n",optind,argv[optind]);*/
        arg_register_error(endtable, endtable, ARG_ENOMATCH, argv[optind++]);
    }

    return;
}