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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  parse_param ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  putl_code (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  puts_code (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  puts_param_types (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_parse_decl(FILE * fp)
{
    putc_code(fp, '\n');
    putl_code(fp, "/* compatibility with bison */\n");
    putl_code(fp, "#ifdef YYPARSE_PARAM\n");
    putl_code(fp, "/* compatibility with FreeBSD */\n");
    putl_code(fp, "# ifdef YYPARSE_PARAM_TYPE\n");
    putl_code(fp,
	      "#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)\n");
    putl_code(fp, "# else\n");
    putl_code(fp, "#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)\n");
    putl_code(fp, "# endif\n");
    putl_code(fp, "#else\n");

    puts_code(fp, "# define YYPARSE_DECL() yyparse(");
    puts_param_types(fp, parse_param, 0);
    putl_code(fp, ")\n");

    putl_code(fp, "#endif\n");
}