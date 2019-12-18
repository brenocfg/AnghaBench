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
 int /*<<< orphan*/  ABS (int /*<<< orphan*/ ) ; 
 scalar_t__ C_plus_plus ; 
 int /*<<< orphan*/  NUL_ec ; 
 int /*<<< orphan*/  OUT_BEGIN_CODE () ; 
 int /*<<< orphan*/  OUT_END_CODE () ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  backing_name ; 
 int /*<<< orphan*/ * backing_up_file ; 
 scalar_t__ backing_up_report ; 
 int /*<<< orphan*/  ccl2ecl () ; 
 int cre8ecs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int csize ; 
 scalar_t__ ddebug ; 
 scalar_t__ do_stdinit ; 
 scalar_t__ do_yylineno ; 
 int /*<<< orphan*/  do_yywrap ; 
 int /*<<< orphan*/ * ecgroup ; 
 int /*<<< orphan*/  flexend (int) ; 
 int /*<<< orphan*/  flexerror (char*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fullspd ; 
 scalar_t__ fulltbl ; 
 scalar_t__ getenv (char*) ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/  lerrsf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lex_compat ; 
 int /*<<< orphan*/  line_directive_out (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nextecm ; 
 int numecs ; 
 int /*<<< orphan*/  out_m4_define (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_str (char*,scalar_t__) ; 
 int /*<<< orphan*/  outn (char*) ; 
 int performance_report ; 
 int /*<<< orphan*/  pinpoint_message (char*) ; 
 int posix_compat ; 
 int real_reject ; 
 scalar_t__ reentrant ; 
 int reject ; 
 int reject_really_used ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ syntaxerror ; 
 scalar_t__ useecs ; 
 scalar_t__ variable_trailing_context_rules ; 
 scalar_t__ yyclass ; 
 int yymore_really_used ; 
 int yymore_used ; 
 scalar_t__ yyparse () ; 
 scalar_t__ yytext_is_array ; 

void readin ()
{
	static char yy_stdinit[] = "FILE *yyin = stdin, *yyout = stdout;";
	static char yy_nostdinit[] =
		"FILE *yyin = (FILE *) 0, *yyout = (FILE *) 0;";

	line_directive_out ((FILE *) 0, 1);

	if (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	if (syntaxerror)
		flexend (1);

	/* If the user explicitly requested posix compatibility by specifing the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	if (posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * posiz, AND check for conflicting options. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	if (getenv ("POSIXLY_CORRECT")) {
		posix_compat = true;
	}

	if (backing_up_report) {
		backing_up_file = fopen (backing_name, "w");
		if (backing_up_file == NULL)
			lerrsf (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	else
		backing_up_file = NULL;

	if (yymore_really_used == true)
		yymore_used = true;
	else if (yymore_really_used == false)
		yymore_used = false;

	if (reject_really_used == true)
		reject = true;
	else if (reject_really_used == false)
		reject = false;

	if (performance_report > 0) {
		if (lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		else if (do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		if (performance_report > 1) {
			if (interactive)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			if (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		if (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		if (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	if (reject)
		real_reject = true;

	if (variable_trailing_context_rules)
		reject = true;

	if ((fulltbl || fullspd) && reject) {
		if (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		else if (do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		else
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	if (reject){
        out_m4_define( "M4_YY_USES_REJECT", NULL);
		//outn ("\n#define YY_USES_REJECT");
    }

	if (!do_yywrap) {
		if (!C_plus_plus) {
			 if (reentrant)
				outn ("\n#define yywrap(yyscanner) 1");
			 else
				outn ("\n#define yywrap() 1");
		}
		outn ("#define YY_SKIP_YYWRAP");
	}

	if (ddebug)
		outn ("\n#define FLEX_DEBUG");

	OUT_BEGIN_CODE ();
	if (csize == 256)
		outn ("typedef unsigned char YY_CHAR;");
	else
		outn ("typedef char YY_CHAR;");
	OUT_END_CODE ();

	if (C_plus_plus) {
		outn ("#define yytext_ptr yytext");

		if (interactive)
			outn ("#define YY_INTERACTIVE");
	}

	else {
		OUT_BEGIN_CODE ();
		/* In reentrant scanner, stdinit is handled in flex.skl. */
		if (do_stdinit) {
			if (reentrant){
                outn ("#ifdef VMS");
                outn ("#ifdef __VMS_POSIX");
                outn ("#define YY_STDINIT");
                outn ("#endif");
                outn ("#else");
                outn ("#define YY_STDINIT");
                outn ("#endif");
            }

			outn ("#ifdef VMS");
			outn ("#ifndef __VMS_POSIX");
			outn (yy_nostdinit);
			outn ("#else");
			outn (yy_stdinit);
			outn ("#endif");
			outn ("#else");
			outn (yy_stdinit);
			outn ("#endif");
		}

		else {
			if(!reentrant)
                outn (yy_nostdinit);
		}
		OUT_END_CODE ();
	}

	OUT_BEGIN_CODE ();
	if (fullspd)
		outn ("typedef yyconst struct yy_trans_info *yy_state_type;");
	else if (!C_plus_plus)
		outn ("typedef int yy_state_type;");
	OUT_END_CODE ();

	if (lex_compat)
		outn ("#define YY_FLEX_LEX_COMPAT");

	if (!C_plus_plus && !reentrant) {
		outn ("extern int yylineno;");
		OUT_BEGIN_CODE ();
		outn ("int yylineno = 1;");
		OUT_END_CODE ();
	}

	if (C_plus_plus) {
		outn ("\n#include <FlexLexer.h>");

 		if (!do_yywrap) {
			outn("\nint yyFlexLexer::yywrap() { return 1; }");
		}

		if (yyclass) {
			outn ("int yyFlexLexer::yylex()");
			outn ("\t{");
			outn ("\tLexerError( \"yyFlexLexer::yylex invoked but %option yyclass used\" );");
			outn ("\treturn 0;");
			outn ("\t}");

			out_str ("\n#define YY_DECL int %s::yylex()\n",
				 yyclass);
		}
	}

	else {

		/* Watch out: yytext_ptr is a variable when yytext is an array,
		 * but it's a macro when yytext is a pointer.
		 */
		if (yytext_is_array) {
			if (!reentrant)
				outn ("extern char yytext[];\n");
		}
		else {
			if (reentrant) {
				outn ("#define yytext_ptr yytext_r");
			}
			else {
				outn ("extern char *yytext;");
				outn ("#define yytext_ptr yytext");
			}
		}

		if (yyclass)
			flexerror (_
				   ("%option yyclass only meaningful for C++ scanners"));
	}

	if (useecs)
		numecs = cre8ecs (nextecm, ecgroup, csize);
	else
		numecs = csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[csize];
	NUL_ec = ABS (ecgroup[0]);

	if (useecs)
		ccl2ecl ();
}