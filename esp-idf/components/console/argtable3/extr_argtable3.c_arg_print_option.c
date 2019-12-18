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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  arg_cat_optionv (char*,int,char const*,char const*,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 

void arg_print_option(FILE *fp,
                      const char *shortopts,
                      const char *longopts,
                      const char *datatype,
                      const char *suffix)
{
    char syntax[200] = "";
    suffix = suffix ? suffix : "";

    /* there is no way of passing the proper optvalue for optional argument values here, so we must ignore it */
    arg_cat_optionv(syntax,
                    sizeof(syntax),
                    shortopts,
                    longopts,
                    datatype,
                    0,
                    "|");

    fputs(syntax, fp);
    fputs(suffix, fp);
}