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
typedef  int /*<<< orphan*/  syntax ;
struct arg_hdr {int flag; char* shortopts; char* longopts; char* datatype; int mincount; int maxcount; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARG_HASOPTVALUE ; 
 int ARG_HASVALUE ; 
 int ARG_TERMINATOR ; 
 int /*<<< orphan*/  arg_cat_option (char*,int,char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  arg_print_gnuswitch (int /*<<< orphan*/ *,struct arg_hdr**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 scalar_t__ strlen (char*) ; 

void arg_print_syntax(FILE *fp, void * *argtable, const char *suffix)
{
    struct arg_hdr * *table = (struct arg_hdr * *)argtable;
    int i, tabindex;

    /* print GNU style [OPTION] string */
    arg_print_gnuswitch(fp, table);

    /* print remaining options in abbreviated style */
    for(tabindex = 0;
        table[tabindex] && !(table[tabindex]->flag & ARG_TERMINATOR);
        tabindex++)
    {
        char syntax[200] = "";
        const char *shortopts, *longopts, *datatype;

        /* skip short options without arg values (they were printed by arg_print_gnu_switch) */
        if (table[tabindex]->shortopts &&
            !(table[tabindex]->flag & ARG_HASVALUE))
            continue;

        shortopts = table[tabindex]->shortopts;
        longopts  = table[tabindex]->longopts;
        datatype  = table[tabindex]->datatype;
        arg_cat_option(syntax,
                       sizeof(syntax),
                       shortopts,
                       longopts,
                       datatype,
                       table[tabindex]->flag & ARG_HASOPTVALUE);

        if (strlen(syntax) > 0)
        {
            /* print mandatory instances of this option */
            for (i = 0; i < table[tabindex]->mincount; i++)
                fprintf(fp, " %s", syntax);

            /* print optional instances enclosed in "[..]" */
            switch ( table[tabindex]->maxcount - table[tabindex]->mincount )
            {
            case 0:
                break;
            case 1:
                fprintf(fp, " [%s]", syntax);
                break;
            case 2:
                fprintf(fp, " [%s] [%s]", syntax, syntax);
                break;
            default:
                fprintf(fp, " [%s]...", syntax);
                break;
            }
        }
    }

    if (suffix)
        fprintf(fp, "%s", suffix);
}