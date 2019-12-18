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
typedef  int /*<<< orphan*/  NUL_ec_str ;

/* Variables and functions */
 int NUL_ec ; 
 int /*<<< orphan*/  do_indent () ; 
 scalar_t__ fullspd ; 
 scalar_t__ fulltbl ; 
 int /*<<< orphan*/  gen_backing_up () ; 
 int /*<<< orphan*/  gen_next_compressed_state (char*) ; 
 scalar_t__ gentables ; 
 int /*<<< orphan*/  indent_down () ; 
 int /*<<< orphan*/  indent_puts (char*) ; 
 int /*<<< orphan*/  indent_up () ; 
 int jamstate ; 
 scalar_t__ nultrans ; 
 scalar_t__ num_backing_up ; 
 int /*<<< orphan*/  out_dec (char*,int) ; 
 int /*<<< orphan*/  outc (char) ; 
 scalar_t__ reject ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void gen_NUL_trans ()
{				/* NOTE - changes in here should be reflected in gen_next_match() */
	/* Only generate a definition for "yy_cp" if we'll generate code
	 * that uses it.  Otherwise lint and the like complain.
	 */
	int     need_backing_up = (num_backing_up > 0 && !reject);

	if (need_backing_up && (!nultrans || fullspd || fulltbl))
		/* We're going to need yy_cp lying around for the call
		 * below to gen_backing_up().
		 */
		indent_puts ("char *yy_cp = YY_G(yy_c_buf_p);");

	outc ('\n');

	if (nultrans) {
		indent_puts
			("yy_current_state = yy_NUL_trans[yy_current_state];");
		indent_puts ("yy_is_jam = (yy_current_state == 0);");
	}

	else if (fulltbl) {
		do_indent ();
		if (gentables)
			out_dec ("yy_current_state = yy_nxt[yy_current_state][%d];\n", NUL_ec);
		else
			out_dec ("yy_current_state = yy_nxt[yy_current_state*YY_NXT_LOLEN + %d];\n", NUL_ec);
		indent_puts ("yy_is_jam = (yy_current_state <= 0);");
	}

	else if (fullspd) {
		do_indent ();
		out_dec ("int yy_c = %d;\n", NUL_ec);

		indent_puts
			("yyconst struct yy_trans_info *yy_trans_info;\n");
		indent_puts
			("yy_trans_info = &yy_current_state[(unsigned int) yy_c];");
		indent_puts ("yy_current_state += yy_trans_info->yy_nxt;");

		indent_puts
			("yy_is_jam = (yy_trans_info->yy_verify != yy_c);");
	}

	else {
		char    NUL_ec_str[20];

		snprintf (NUL_ec_str, sizeof(NUL_ec_str), "%d", NUL_ec);
		gen_next_compressed_state (NUL_ec_str);

		do_indent ();
		out_dec ("yy_is_jam = (yy_current_state == %d);\n",
			 jamstate);

		if (reject) {
			/* Only stack this state if it's a transition we
			 * actually make.  If we stack it on a jam, then
			 * the state stack and yy_c_buf_p get out of sync.
			 */
			indent_puts ("if ( ! yy_is_jam )");
			indent_up ();
			indent_puts
				("*YY_G(yy_state_ptr)++ = yy_current_state;");
			indent_down ();
		}
	}

	/* If we've entered an accepting state, back up; note that
	 * compressed tables have *already* done such backing up, so
	 * we needn't bother with it again.
	 */
	if (need_backing_up && (fullspd || fulltbl)) {
		outc ('\n');
		indent_puts ("if ( ! yy_is_jam )");
		indent_up ();
		indent_puts ("{");
		gen_backing_up ();
		indent_puts ("}");
		indent_down ();
	}
}