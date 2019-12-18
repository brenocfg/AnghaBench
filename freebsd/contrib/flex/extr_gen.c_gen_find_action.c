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

/* Variables and functions */
 scalar_t__ fullspd ; 
 scalar_t__ fulltbl ; 
 int /*<<< orphan*/  indent_down () ; 
 int /*<<< orphan*/  indent_puts (char*) ; 
 int /*<<< orphan*/  indent_up () ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/  outn (char*) ; 
 scalar_t__ real_reject ; 
 scalar_t__ reject ; 
 scalar_t__ variable_trailing_context_rules ; 

void gen_find_action ()
{
	if (fullspd)
		indent_puts ("yy_act = yy_current_state[-1].yy_nxt;");

	else if (fulltbl)
		indent_puts ("yy_act = yy_accept[yy_current_state];");

	else if (reject) {
		indent_puts ("yy_current_state = *--YY_G(yy_state_ptr);");
		indent_puts ("YY_G(yy_lp) = yy_accept[yy_current_state];");

		outn ("goto find_rule; /* avoid `defined but not used' warning */");
		outn ("find_rule: /* we branch to this label when backing up */");

		indent_puts
			("for ( ; ; ) /* until we find what rule we matched */");

		indent_up ();

		indent_puts ("{");

		indent_puts
			("if ( YY_G(yy_lp) && YY_G(yy_lp) < yy_accept[yy_current_state + 1] )");
		indent_up ();
		indent_puts ("{");
		indent_puts ("yy_act = yy_acclist[YY_G(yy_lp)];");

		if (variable_trailing_context_rules) {
			indent_puts
				("if ( yy_act & YY_TRAILING_HEAD_MASK ||");
			indent_puts ("     YY_G(yy_looking_for_trail_begin) )");
			indent_up ();
			indent_puts ("{");

			indent_puts
				("if ( yy_act == YY_G(yy_looking_for_trail_begin) )");
			indent_up ();
			indent_puts ("{");
			indent_puts ("YY_G(yy_looking_for_trail_begin) = 0;");
			indent_puts ("yy_act &= ~YY_TRAILING_HEAD_MASK;");
			indent_puts ("break;");
			indent_puts ("}");
			indent_down ();

			indent_puts ("}");
			indent_down ();

			indent_puts
				("else if ( yy_act & YY_TRAILING_MASK )");
			indent_up ();
			indent_puts ("{");
			indent_puts
				("YY_G(yy_looking_for_trail_begin) = yy_act & ~YY_TRAILING_MASK;");
			indent_puts
				("YY_G(yy_looking_for_trail_begin) |= YY_TRAILING_HEAD_MASK;");

			if (real_reject) {
				/* Remember matched text in case we back up
				 * due to REJECT.
				 */
				indent_puts
					("YY_G(yy_full_match) = yy_cp;");
				indent_puts
					("YY_G(yy_full_state) = YY_G(yy_state_ptr);");
				indent_puts ("YY_G(yy_full_lp) = YY_G(yy_lp);");
			}

			indent_puts ("}");
			indent_down ();

			indent_puts ("else");
			indent_up ();
			indent_puts ("{");
			indent_puts ("YY_G(yy_full_match) = yy_cp;");
			indent_puts
				("YY_G(yy_full_state) = YY_G(yy_state_ptr);");
			indent_puts ("YY_G(yy_full_lp) = YY_G(yy_lp);");
			indent_puts ("break;");
			indent_puts ("}");
			indent_down ();

			indent_puts ("++YY_G(yy_lp);");
			indent_puts ("goto find_rule;");
		}

		else {
			/* Remember matched text in case we back up due to
			 * trailing context plus REJECT.
			 */
			indent_up ();
			indent_puts ("{");
			indent_puts ("YY_G(yy_full_match) = yy_cp;");
			indent_puts ("break;");
			indent_puts ("}");
			indent_down ();
		}

		indent_puts ("}");
		indent_down ();

		indent_puts ("--yy_cp;");

		/* We could consolidate the following two lines with those at
		 * the beginning, but at the cost of complaints that we're
		 * branching inside a loop.
		 */
		indent_puts ("yy_current_state = *--YY_G(yy_state_ptr);");
		indent_puts ("YY_G(yy_lp) = yy_accept[yy_current_state];");

		indent_puts ("}");

		indent_down ();
	}

	else {			/* compressed */
		indent_puts ("yy_act = yy_accept[yy_current_state];");

		if (interactive && !reject) {
			/* Do the guaranteed-needed backing up to figure out
			 * the match.
			 */
			indent_puts ("if ( yy_act == 0 )");
			indent_up ();
			indent_puts ("{ /* have to back up */");
			indent_puts
				("yy_cp = YY_G(yy_last_accepting_cpos);");
			indent_puts
				("yy_current_state = YY_G(yy_last_accepting_state);");
			indent_puts
				("yy_act = yy_accept[yy_current_state];");
			indent_puts ("}");
			indent_down ();
		}
	}
}