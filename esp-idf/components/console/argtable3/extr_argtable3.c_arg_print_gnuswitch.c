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
struct arg_hdr {int flag; int mincount; char const** shortopts; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARG_HASVALUE ; 
 int ARG_TERMINATOR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static
void arg_print_gnuswitch(FILE *fp, struct arg_hdr * *table)
{
    int tabindex;
    const char *format1 = " -%c";
    const char *format2 = " [-%c";
    const char *suffix = "";

    /* print all mandatory switches that are without argument values */
    for(tabindex = 0;
        table[tabindex] && !(table[tabindex]->flag & ARG_TERMINATOR);
        tabindex++)
    {
        /* skip optional options */
        if (table[tabindex]->mincount < 1)
            continue;

        /* skip non-short options */
        if (table[tabindex]->shortopts == NULL)
            continue;

        /* skip options that take argument values */
        if (table[tabindex]->flag & ARG_HASVALUE)
            continue;

        /* print the short option (only the first short option char, ignore multiple choices)*/
        fprintf(fp, format1, table[tabindex]->shortopts[0]);
        format1 = "%c";
        format2 = "[%c";
    }

    /* print all optional switches that are without argument values */
    for(tabindex = 0;
        table[tabindex] && !(table[tabindex]->flag & ARG_TERMINATOR);
        tabindex++)
    {
        /* skip mandatory args */
        if (table[tabindex]->mincount > 0)
            continue;

        /* skip args without short options */
        if (table[tabindex]->shortopts == NULL)
            continue;

        /* skip args with values */
        if (table[tabindex]->flag & ARG_HASVALUE)
            continue;

        /* print first short option */
        fprintf(fp, format2, table[tabindex]->shortopts[0]);
        format2 = "%c";
        suffix = "]";
    }

    fprintf(fp, "%s", suffix);
}