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
 int /*<<< orphan*/  indent_puts (char*) ; 
 scalar_t__ num_backing_up ; 
 int /*<<< orphan*/  outc (char) ; 
 scalar_t__ reject ; 
 int /*<<< orphan*/  set_indent (int) ; 

void gen_bu_action ()
{
	if (reject || num_backing_up == 0)
		return;

	set_indent (3);

	indent_puts ("case 0: /* must back up */");
	indent_puts ("/* undo the effects of YY_DO_BEFORE_ACTION */");
	indent_puts ("*yy_cp = YY_G(yy_hold_char);");

	if (fullspd || fulltbl)
		indent_puts ("yy_cp = YY_G(yy_last_accepting_cpos) + 1;");
	else
		/* Backing-up info for compressed tables is taken \after/
		 * yy_cp has been incremented for the next state.
		 */
		indent_puts ("yy_cp = YY_G(yy_last_accepting_cpos);");

	indent_puts ("yy_current_state = YY_G(yy_last_accepting_state);");
	indent_puts ("goto yy_find_action;");
	outc ('\n');

	set_indent (0);
}