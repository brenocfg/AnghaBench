#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dfaacc_state; } ;

/* Variables and functions */
 int ACTION_POSITION ; 
 int EOB_POSITION ; 
 int* base ; 
 int* chk ; 
 int current_max_dfas ; 
 int current_max_xpairs ; 
 int /*<<< orphan*/  dataend () ; 
 TYPE_1__* dfaacc ; 
 int /*<<< orphan*/  expand_nxt_chk () ; 
 int /*<<< orphan*/  genecs () ; 
 scalar_t__ gentables ; 
 int /*<<< orphan*/  increase_max_dfas () ; 
 int lastdfa ; 
 int lastsc ; 
 int num_rules ; 
 int numecs ; 
 size_t* nxt ; 
 int /*<<< orphan*/  out_dec (char*,int) ; 
 int /*<<< orphan*/  outn (char*) ; 
 int tblend ; 
 int /*<<< orphan*/  transition_struct_out (int,size_t) ; 
 scalar_t__ useecs ; 

void genctbl ()
{
	int i;
	int     end_of_buffer_action = num_rules + 1;

	/* Table of verify for transition and offset to next state. */
	if (gentables)
		out_dec ("static yyconst struct yy_trans_info yy_transition[%d] =\n    {\n", tblend + numecs + 1);
	else
		outn ("static yyconst struct yy_trans_info *yy_transition = 0;");

	/* We want the transition to be represented as the offset to the
	 * next state, not the actual state number, which is what it currently
	 * is.  The offset is base[nxt[i]] - (base of current state)].  That's
	 * just the difference between the starting points of the two involved
	 * states (to - from).
	 *
	 * First, though, we need to find some way to put in our end-of-buffer
	 * flags and states.  We do this by making a state with absolutely no
	 * transitions.  We put it at the end of the table.
	 */

	/* We need to have room in nxt/chk for two more slots: One for the
	 * action and one for the end-of-buffer transition.  We now *assume*
	 * that we're guaranteed the only character we'll try to index this
	 * nxt/chk pair with is EOB, i.e., 0, so we don't have to make sure
	 * there's room for jam entries for other characters.
	 */

	while (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	while (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	base[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = end_of_buffer_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	for (i = 0; i <= lastdfa; ++i) {
		int     anum = dfaacc[i].dfaacc_state;
		int     offset = base[i];

		chk[offset] = EOB_POSITION;
		chk[offset - 1] = ACTION_POSITION;
		nxt[offset - 1] = anum;	/* action number */
	}

	for (i = 0; i <= tblend; ++i) {
		if (chk[i] == EOB_POSITION)
			transition_struct_out (0, base[lastdfa + 1] - i);

		else if (chk[i] == ACTION_POSITION)
			transition_struct_out (0, nxt[i]);

		else if (chk[i] > numecs || chk[i] == 0)
			transition_struct_out (0, 0);	/* unused slot */

		else		/* verify, transition */
			transition_struct_out (chk[i],
					       base[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_out (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_out (chk[tblend + 2], nxt[tblend + 2]);

	if (gentables)
		outn ("    };\n");

	/* Table of pointers to start states. */
	if (gentables)
		out_dec ("static yyconst struct yy_trans_info *yy_start_state_list[%d] =\n", lastsc * 2 + 1);
	else
		outn ("static yyconst struct yy_trans_info **yy_start_state_list =0;");

	if (gentables) {
		outn ("    {");

		for (i = 0; i <= lastsc * 2; ++i)
			out_dec ("    &yy_transition[%d],\n", base[i]);

		dataend ();
	}

	if (useecs)
		genecs ();
}