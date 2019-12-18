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
struct si_sm_data {int dummy; } ;

/* Variables and functions */
 int BT_INTMASK_R ; 
 int BT_STATUS ; 
 int /*<<< orphan*/  reset_flags (struct si_sm_data*) ; 

__attribute__((used)) static int bt_detect(struct si_sm_data *bt)
{
	/*
	 * It's impossible for the BT status and interrupt registers to be
	 * all 1's, (assuming a properly functioning, self-initialized BMC)
	 * but that's what you get from reading a bogus address, so we
	 * test that first.  The calling routine uses negative logic.
	 */

	if ((BT_STATUS == 0xFF) && (BT_INTMASK_R == 0xFF))
		return 1;
	reset_flags(bt);
	return 0;
}