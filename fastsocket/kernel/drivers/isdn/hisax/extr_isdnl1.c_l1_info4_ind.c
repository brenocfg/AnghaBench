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
struct TYPE_2__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  timer; int /*<<< orphan*/  (* l1hw ) (struct PStack*,int,int /*<<< orphan*/ *) ;} ;
struct PStack {TYPE_1__ l1; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMER_ACT ; 
 int /*<<< orphan*/  FLG_L1_ACTIVATED ; 
 int /*<<< orphan*/  FLG_L1_ACTTIMER ; 
 int /*<<< orphan*/  FLG_L1_DEACTTIMER ; 
 int /*<<< orphan*/  FLG_L1_T3RUN ; 
 int /*<<< orphan*/  FLG_L1_UINT ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmRestartTimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int HW_INFO3 ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_L1_F7 ; 
 int /*<<< orphan*/  ST_L1_TRANS ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_info4_ind(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

#ifdef HISAX_UINTERFACE
	if (test_bit(FLG_L1_UINT, &st->l1.Flags))
		FsmChangeState(fi, ST_L1_TRANS);
	else
#endif
		FsmChangeState(fi, ST_L1_F7);
	st->l1.l1hw(st, HW_INFO3 | REQUEST, NULL);
	if (test_and_clear_bit(FLG_L1_DEACTTIMER, &st->l1.Flags))
		FsmDelTimer(&st->l1.timer, 4);
	if (!test_bit(FLG_L1_ACTIVATED, &st->l1.Flags)) {
		if (test_and_clear_bit(FLG_L1_T3RUN, &st->l1.Flags))
			FsmDelTimer(&st->l1.timer, 3);
		FsmRestartTimer(&st->l1.timer, 110, EV_TIMER_ACT, NULL, 2);
		test_and_set_bit(FLG_L1_ACTTIMER, &st->l1.Flags);
	}
}