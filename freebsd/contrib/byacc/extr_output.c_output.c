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
 int /*<<< orphan*/  body_1 ; 
 int /*<<< orphan*/  body_2 ; 
 int /*<<< orphan*/  body_3 ; 
 int /*<<< orphan*/  body_vars ; 
 int /*<<< orphan*/ * code_file ; 
 int /*<<< orphan*/ * defines_file ; 
 char* defines_file_name ; 
 scalar_t__ destructor ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/  end_defines_file () ; 
 int /*<<< orphan*/ * externs_file ; 
 char* externs_file_name ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free_itemsets () ; 
 int /*<<< orphan*/  free_parser () ; 
 int /*<<< orphan*/  free_reductions () ; 
 int /*<<< orphan*/  free_shifts () ; 
 int /*<<< orphan*/  global_vars ; 
 int /*<<< orphan*/  hdr_defs ; 
 int /*<<< orphan*/  hdr_vars ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  impure_vars ; 
 int /*<<< orphan*/  init_vars ; 
 scalar_t__ initial_action ; 
 scalar_t__ locations ; 
 int /*<<< orphan*/  outline ; 
 int /*<<< orphan*/  output_YYINT_typedef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_accessing_symbols () ; 
 int /*<<< orphan*/  output_actions () ; 
 int /*<<< orphan*/  output_backtracking_parser (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_debug () ; 
 int /*<<< orphan*/  output_defines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_error_decl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_externs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * output_file ; 
 int /*<<< orphan*/  output_initial_action () ; 
 int /*<<< orphan*/  output_lex_decl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_ltype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_no_leaks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_parse_decl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_pure_parser (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_rule_data () ; 
 int /*<<< orphan*/  output_semantic_actions () ; 
 int /*<<< orphan*/  output_stored_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_stype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_trailing_text () ; 
 int /*<<< orphan*/  output_yydefred () ; 
 int /*<<< orphan*/  output_yydestruct_decl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_yydestruct_impl () ; 
 scalar_t__ pure_parser ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,char) ; 
 scalar_t__ rflag ; 
 int /*<<< orphan*/  start_defines_file () ; 
 int /*<<< orphan*/  tables ; 
 int /*<<< orphan*/  trailer ; 
 int /*<<< orphan*/  write_code_lineno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdecls ; 

void
output(void)
{
    FILE *fp;

    free_itemsets();
    free_shifts();
    free_reductions();

#if defined(YYBTYACC)
    output_backtracking_parser(output_file);
    if (rflag)
	output_backtracking_parser(code_file);
#endif

    if (iflag)
    {
	write_code_lineno(code_file);
	++outline;
	fprintf(code_file, "#include \"%s\"\n", externs_file_name);
	fp = externs_file;
    }
    else
	fp = code_file;

    output_prefix(fp);
    output_pure_parser(fp);
#if defined(YY_NO_LEAKS)
    output_no_leaks(fp);
#endif
    output_stored_text(fp);
    output_stype(fp);
#if defined(YYBTYACC)
    if (locations)
	output_ltype(fp);
#endif
    output_parse_decl(fp);
    output_lex_decl(fp);
    output_error_decl(fp);
#if defined(YYBTYACC)
    if (destructor)
	output_yydestruct_decl(fp);
#endif
    if (iflag || !rflag)
    {
	write_section(fp, xdecls);
    }

    if (iflag)
    {
	output_externs(externs_file, global_vars);
	if (!pure_parser)
	    output_externs(externs_file, impure_vars);
    }

    if (iflag)
    {
	if (dflag)
	{
	    ++outline;
	    fprintf(code_file, "#include \"%s\"\n", defines_file_name);
	}
	else
	    output_defines(externs_file);
    }
    else
    {
	putc_code(code_file, '\n');
	output_defines(code_file);
    }

    if (dflag)
    {
	start_defines_file();
	output_defines(defines_file);
	end_defines_file();
    }

    output_rule_data();
    output_yydefred();
#if defined(YYBTYACC)
    output_accessing_symbols();
#endif
    output_actions();
    free_parser();
    output_debug();
    if (rflag)
    {
	write_section(code_file, xdecls);
	output_YYINT_typedef(code_file);
	write_section(code_file, tables);
    }
    write_section(code_file, global_vars);
    if (!pure_parser)
    {
	write_section(code_file, impure_vars);
    }
    write_section(code_file, hdr_defs);
    if (!pure_parser)
    {
	write_section(code_file, hdr_vars);
    }
    output_trailing_text();
#if defined(YYBTYACC)
    if (destructor)
	output_yydestruct_impl();
#endif
    write_section(code_file, body_1);
    if (pure_parser)
    {
	write_section(code_file, body_vars);
    }
    write_section(code_file, body_2);
    if (pure_parser)
    {
	write_section(code_file, init_vars);
    }
#if defined(YYBTYACC)
    if (initial_action)
	output_initial_action();
#endif
    write_section(code_file, body_3);
    output_semantic_actions();
    write_section(code_file, trailer);
}