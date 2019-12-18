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
 scalar_t__ CountLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  define_prefixed (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ locations ; 
 int /*<<< orphan*/  outline ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  putl_code (int /*<<< orphan*/ *,char*) ; 
 char* symbol_prefix ; 

__attribute__((used)) static void
output_prefix(FILE * fp)
{
    if (symbol_prefix == NULL)
    {
	symbol_prefix = "yy";
    }
    else
    {
	define_prefixed(fp, "yyparse");
	define_prefixed(fp, "yylex");
	define_prefixed(fp, "yyerror");
	define_prefixed(fp, "yychar");
	define_prefixed(fp, "yyval");
	define_prefixed(fp, "yylval");
	define_prefixed(fp, "yydebug");
	define_prefixed(fp, "yynerrs");
	define_prefixed(fp, "yyerrflag");
	define_prefixed(fp, "yylhs");
	define_prefixed(fp, "yylen");
	define_prefixed(fp, "yydefred");
#if defined(YYBTYACC)
	define_prefixed(fp, "yystos");
#endif
	define_prefixed(fp, "yydgoto");
	define_prefixed(fp, "yysindex");
	define_prefixed(fp, "yyrindex");
	define_prefixed(fp, "yygindex");
	define_prefixed(fp, "yytable");
	define_prefixed(fp, "yycheck");
	define_prefixed(fp, "yyname");
	define_prefixed(fp, "yyrule");
#if defined(YYBTYACC)
	if (locations)
	{
	    define_prefixed(fp, "yyloc");
	    define_prefixed(fp, "yylloc");
	}
	putc_code(fp, '\n');
	putl_code(fp, "#if YYBTYACC\n");

	define_prefixed(fp, "yycindex");
	define_prefixed(fp, "yyctable");

	putc_code(fp, '\n');
	putl_code(fp, "#endif /* YYBTYACC */\n");
	putc_code(fp, '\n');
#endif
    }
    if (CountLine(fp))
	++outline;
    fprintf(fp, "#define YYPREFIX \"%s\"\n", symbol_prefix);
}