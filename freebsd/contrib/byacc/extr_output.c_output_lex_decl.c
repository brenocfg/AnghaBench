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
 scalar_t__ lex_param ; 
 scalar_t__ locations ; 
 scalar_t__ pure_parser ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  putl_code (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  puts_code (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  puts_param_names (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts_param_types (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_lex_decl(FILE * fp)
{
    putc_code(fp, '\n');
    putl_code(fp, "/* Parameters sent to lex. */\n");
    putl_code(fp, "#ifdef YYLEX_PARAM\n");
    if (pure_parser)
    {
	putl_code(fp, "# ifdef YYLEX_PARAM_TYPE\n");
#if defined(YYBTYACC)
	if (locations)
	{
	    putl_code(fp, "#  define YYLEX_DECL() yylex(YYSTYPE *yylval,"
		      " YYLTYPE *yylloc,"
		      " YYLEX_PARAM_TYPE YYLEX_PARAM)\n");
	}
	else
#endif
	{
	    putl_code(fp, "#  define YYLEX_DECL() yylex(YYSTYPE *yylval,"
		      " YYLEX_PARAM_TYPE YYLEX_PARAM)\n");
	}
	putl_code(fp, "# else\n");
#if defined(YYBTYACC)
	if (locations)
	{
	    putl_code(fp, "#  define YYLEX_DECL() yylex(YYSTYPE *yylval,"
		      " YYLTYPE *yylloc,"
		      " void * YYLEX_PARAM)\n");
	}
	else
#endif
	{
	    putl_code(fp, "#  define YYLEX_DECL() yylex(YYSTYPE *yylval,"
		      " void * YYLEX_PARAM)\n");
	}
	putl_code(fp, "# endif\n");
#if defined(YYBTYACC)
	if (locations)
	    putl_code(fp,
		      "# define YYLEX yylex(&yylval, &yylloc, YYLEX_PARAM)\n");
	else
#endif
	    putl_code(fp, "# define YYLEX yylex(&yylval, YYLEX_PARAM)\n");
    }
    else
    {
	putl_code(fp, "# define YYLEX_DECL() yylex(void *YYLEX_PARAM)\n");
	putl_code(fp, "# define YYLEX yylex(YYLEX_PARAM)\n");
    }
    putl_code(fp, "#else\n");
    if (pure_parser && lex_param)
    {
#if defined(YYBTYACC)
	if (locations)
	    puts_code(fp,
		      "# define YYLEX_DECL() yylex(YYSTYPE *yylval, YYLTYPE *yylloc, ");
	else
#endif
	    puts_code(fp, "# define YYLEX_DECL() yylex(YYSTYPE *yylval, ");
	puts_param_types(fp, lex_param, 0);
	putl_code(fp, ")\n");

#if defined(YYBTYACC)
	if (locations)
	    puts_code(fp, "# define YYLEX yylex(&yylval, &yylloc, ");
	else
#endif
	    puts_code(fp, "# define YYLEX yylex(&yylval, ");
	puts_param_names(fp, lex_param, 0);
	putl_code(fp, ")\n");
    }
    else if (pure_parser)
    {
#if defined(YYBTYACC)
	if (locations)
	{
	    putl_code(fp,
		      "# define YYLEX_DECL() yylex(YYSTYPE *yylval, YYLTYPE *yylloc)\n");
	    putl_code(fp, "# define YYLEX yylex(&yylval, &yylloc)\n");
	}
	else
#endif
	{
	    putl_code(fp, "# define YYLEX_DECL() yylex(YYSTYPE *yylval)\n");
	    putl_code(fp, "# define YYLEX yylex(&yylval)\n");
	}
    }
    else if (lex_param)
    {
	puts_code(fp, "# define YYLEX_DECL() yylex(");
	puts_param_types(fp, lex_param, 0);
	putl_code(fp, ")\n");

	puts_code(fp, "# define YYLEX yylex(");
	puts_param_names(fp, lex_param, 0);
	putl_code(fp, ")\n");
    }
    else
    {
	putl_code(fp, "# define YYLEX_DECL() yylex(void)\n");
	putl_code(fp, "# define YYLEX yylex()\n");
    }
    putl_code(fp, "#endif\n");
}