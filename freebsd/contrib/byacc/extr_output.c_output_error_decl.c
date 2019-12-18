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
 scalar_t__ locations ; 
 int /*<<< orphan*/  parse_param ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  putl_code (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  puts_code (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  puts_param_names (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  puts_param_types (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
output_error_decl(FILE * fp)
{
    putc_code(fp, '\n');
    putl_code(fp, "/* Parameters sent to yyerror. */\n");
    putl_code(fp, "#ifndef YYERROR_DECL\n");
    puts_code(fp, "#define YYERROR_DECL() yyerror(");
#if defined(YYBTYACC)
    if (locations)
	puts_code(fp, "YYLTYPE *loc, ");
#endif
    puts_param_types(fp, parse_param, 1);
    putl_code(fp, "const char *s)\n");
    putl_code(fp, "#endif\n");

    putl_code(fp, "#ifndef YYERROR_CALL\n");

    puts_code(fp, "#define YYERROR_CALL(msg) yyerror(");
#if defined(YYBTYACC)
    if (locations)
	puts_code(fp, "&yylloc, ");
#endif
    puts_param_names(fp, parse_param, 1);
    putl_code(fp, "msg)\n");

    putl_code(fp, "#endif\n");
}