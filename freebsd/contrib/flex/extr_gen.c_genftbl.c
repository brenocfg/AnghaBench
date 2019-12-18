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
 char* _ (char*) ; 
 int /*<<< orphan*/  dataend () ; 
 TYPE_1__* dfaacc ; 
 size_t end_of_buffer_state ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  genecs () ; 
 int /*<<< orphan*/  get_int16_decl () ; 
 int /*<<< orphan*/  get_int32_decl () ; 
 int lastdfa ; 
 scalar_t__ long_align ; 
 int /*<<< orphan*/  mkdata (int) ; 
 int num_rules ; 
 int /*<<< orphan*/  out_str_dec (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ trace ; 
 scalar_t__ useecs ; 

void genftbl ()
{
	int i;
	int     end_of_buffer_action = num_rules + 1;

	out_str_dec (long_align ? get_int32_decl () : get_int16_decl (),
		     "yy_accept", lastdfa + 1);

	dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

	for (i = 1; i <= lastdfa; ++i) {
		int anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		if (trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend ();

	if (useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}