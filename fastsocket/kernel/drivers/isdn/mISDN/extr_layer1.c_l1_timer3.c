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
struct TYPE_2__ {scalar_t__ state; } ;
struct layer1 {int /*<<< orphan*/  dch; int /*<<< orphan*/  (* dcb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ l1m; int /*<<< orphan*/  Flags; } ;
struct FsmInst {struct layer1* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L1_ACTIVATING ; 
 int /*<<< orphan*/  FLG_L1_DBLOCKED ; 
 int /*<<< orphan*/  FLG_L1_T3RUN ; 
 int /*<<< orphan*/  HW_D_NOBLOCKED ; 
 int /*<<< orphan*/  HW_POWERUP_REQ ; 
 int /*<<< orphan*/  PH_DEACTIVATE_IND ; 
 int /*<<< orphan*/  ST_L1_F3 ; 
 scalar_t__ ST_L1_F6 ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_timer3(struct FsmInst *fi, int event, void *arg)
{
	struct layer1 *l1 = fi->userdata;

	test_and_clear_bit(FLG_L1_T3RUN, &l1->Flags);
	if (test_and_clear_bit(FLG_L1_ACTIVATING, &l1->Flags)) {
		if (test_and_clear_bit(FLG_L1_DBLOCKED, &l1->Flags))
			l1->dcb(l1->dch, HW_D_NOBLOCKED);
		l1->dcb(l1->dch, PH_DEACTIVATE_IND);
	}
	if (l1->l1m.state != ST_L1_F6) {
		mISDN_FsmChangeState(fi, ST_L1_F3);
		l1->dcb(l1->dch, HW_POWERUP_REQ);
	}
}