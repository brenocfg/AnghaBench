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
 int /*<<< orphan*/  arg_print_formatted (int /*<<< orphan*/ *,int,int,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int strlen (char*) ; 

void arg_print_glossary_gnu(FILE *fp, void * *argtable )
{
    struct arg_hdr * *table = (struct arg_hdr * *)argtable;
    int tabindex;

    for(tabindex = 0; !(table[tabindex]->flag & ARG_TERMINATOR); tabindex++)
    {
        if (table[tabindex]->glossary)
        {
            char syntax[200] = "";
            const char *shortopts = table[tabindex]->shortopts;
            const char *longopts  = table[tabindex]->longopts;
            const char *datatype  = table[tabindex]->datatype;
            const char *glossary  = table[tabindex]->glossary;

            if ( !shortopts && longopts )
            {
                /* Indent trailing line by 4 spaces... */
                memset( syntax, ' ', 4 );
                *(syntax + 4) = '\0';
            }

            arg_cat_optionv(syntax,
                            sizeof(syntax),
                            shortopts,
                            longopts,
                            datatype,
                            table[tabindex]->flag & ARG_HASOPTVALUE,
                            ", ");

            /* If syntax fits not into column, print glossary in new line... */
            if ( strlen(syntax) > 25 )
            {
                fprintf( fp, "  %-25s %s\n", syntax, "" );
                *syntax = '\0';
            }

            fprintf( fp, "  %-25s ", syntax );
            arg_print_formatted( fp, 28, 79, glossary );
        }
    } /* for each table entry */

    fputc( '\n', fp );
}