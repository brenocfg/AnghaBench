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
 int EOF ; 
 int /*<<< orphan*/ * code_file ; 
 int /*<<< orphan*/ * defines_file ; 
 int /*<<< orphan*/  dflag ; 
 int /*<<< orphan*/ * externs_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int getc (scalar_t__) ; 
 scalar_t__ iflag ; 
 scalar_t__ is_C_identifier (char*) ; 
 scalar_t__ locations ; 
 int ntokens ; 
 int /*<<< orphan*/  outline ; 
 int /*<<< orphan*/  output_ltype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rewind (scalar_t__) ; 
 scalar_t__ rflag ; 
 int /*<<< orphan*/  sflag ; 
 char** symbol_name ; 
 char* symbol_prefix ; 
 int* symbol_value ; 
 scalar_t__ token_table ; 
 scalar_t__ union_file ; 
 scalar_t__ unionized ; 

__attribute__((used)) static void
output_defines(FILE * fp)
{
    int c, i;
    char *s;

    for (i = 2; i < ntokens; ++i)
    {
	s = symbol_name[i];
	if (is_C_identifier(s) && (!sflag || *s != '"'))
	{
	    fprintf(fp, "#define ");
	    c = *s;
	    if (c == '"')
	    {
		while ((c = *++s) != '"')
		{
		    putc(c, fp);
		}
	    }
	    else
	    {
		do
		{
		    putc(c, fp);
		}
		while ((c = *++s) != 0);
	    }
	    if (fp == code_file)
		++outline;
	    fprintf(fp, " %d\n", symbol_value[i]);
	}
    }

    if (fp == code_file)
	++outline;
    if (fp != defines_file || iflag)
	fprintf(fp, "#define YYERRCODE %d\n", symbol_value[1]);

    if (token_table && rflag && fp != externs_file)
    {
	if (fp == code_file)
	    ++outline;
	fputs("#undef yytname\n", fp);
	if (fp == code_file)
	    ++outline;
	fputs("#define yytname yyname\n", fp);
    }

    if (fp == defines_file || (iflag && !dflag))
    {
	if (unionized)
	{
	    if (union_file != 0)
	    {
		rewind(union_file);
		while ((c = getc(union_file)) != EOF)
		    putc_code(fp, c);
	    }
	    fprintf(fp, "extern YYSTYPE %slval;\n", symbol_prefix);
	}
#if defined(YYBTYACC)
	if (locations)
	    output_ltype(fp);
#endif
    }
}