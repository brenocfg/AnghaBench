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
struct arg_hdr {int flag; char* glossary; char* shortopts; char* longopts; char* datatype; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARG_HASOPTVALUE ; 
 int ARG_TERMINATOR ; 
 int /*<<< orphan*/  arg_cat_optionv (char*,int,char const*,char const*,char const*,int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,char*,char const*) ; 

void arg_print_glossary(FILE *fp, void * *argtable, const char *format)
{
    struct arg_hdr * *table = (struct arg_hdr * *)argtable;
    int tabindex;

    format = format ? format : "  %-20s %s\n";
    for (tabindex = 0; !(table[tabindex]->flag & ARG_TERMINATOR); tabindex++)
    {
        if (table[tabindex]->glossary)
        {
            char syntax[200] = "";
            const char *shortopts = table[tabindex]->shortopts;
            const char *longopts  = table[tabindex]->longopts;
            const char *datatype  = table[tabindex]->datatype;
            const char *glossary  = table[tabindex]->glossary;
            arg_cat_optionv(syntax,
                            sizeof(syntax),
                            shortopts,
                            longopts,
                            datatype,
                            table[tabindex]->flag & ARG_HASOPTVALUE,
                            ", ");
            fprintf(fp, format, syntax, glossary);
        }
    }
}