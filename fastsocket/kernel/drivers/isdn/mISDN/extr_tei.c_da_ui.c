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
struct manager {int /*<<< orphan*/  datimer; int /*<<< orphan*/  options; } ;
struct FsmInst {struct manager* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATIMER_VAL ; 
 int /*<<< orphan*/  EV_DATIMER ; 
 int /*<<< orphan*/  OPTION_L1_HOLD ; 
 int /*<<< orphan*/  mISDN_FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
da_ui(struct FsmInst *fi, int event, void *arg)
{
	struct manager	*mgr = fi->userdata;

	/* restart da timer */
	if (!test_bit(OPTION_L1_HOLD, &mgr->options)) {
		mISDN_FsmDelTimer(&mgr->datimer, 2);
		mISDN_FsmAddTimer(&mgr->datimer, DATIMER_VAL, EV_DATIMER,
			NULL, 2);
	}
}