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
 int /*<<< orphan*/  indent_down () ; 
 int /*<<< orphan*/  indent_puts (char*) ; 
 int /*<<< orphan*/  indent_up () ; 
 scalar_t__ num_backing_up ; 
 scalar_t__ reject ; 

void gen_backing_up ()
{
	if (reject || num_backing_up == 0)
		return;

	if (fullspd)
		indent_puts ("if ( yy_current_state[-1].yy_nxt )");
	else
		indent_puts ("if ( yy_accept[yy_current_state] )");

	indent_up ();
	indent_puts ("{");
	indent_puts ("YY_G(yy_last_accepting_state) = yy_current_state;");
	indent_puts ("YY_G(yy_last_accepting_cpos) = yy_cp;");
	indent_puts ("}");
	indent_down ();
}