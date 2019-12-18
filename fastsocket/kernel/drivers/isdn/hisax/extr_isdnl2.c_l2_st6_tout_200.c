#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rc; scalar_t__ N200; int /*<<< orphan*/  T200; int /*<<< orphan*/  t200; int /*<<< orphan*/  flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* layer ) (struct PStack*,int,void*) ;} ;
struct PStack {TYPE_2__ l2; TYPE_1__ ma; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  CONFIRM ; 
 int DISC ; 
 int /*<<< orphan*/  EV_L2_T200 ; 
 int /*<<< orphan*/  FLG_DCHAN_BUSY ; 
 int /*<<< orphan*/  FLG_LAPD ; 
 int /*<<< orphan*/  FLG_T200_RUN ; 
 int /*<<< orphan*/  FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int INDICATION ; 
 int MDL_ERROR ; 
 int /*<<< orphan*/  ST_L2_4 ; 
 int /*<<< orphan*/  lapb_dl_release_l2l3 (struct PStack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_uframe (struct PStack*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,void*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_st6_tout_200(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

	if (test_bit(FLG_LAPD, &st->l2.flag) &&
		test_bit(FLG_DCHAN_BUSY, &st->l2.flag)) {
		FsmAddTimer(&st->l2.t200, st->l2.T200, EV_L2_T200, NULL, 9);
	} else if (st->l2.rc == st->l2.N200) {
		FsmChangeState(fi, ST_L2_4);
		test_and_clear_bit(FLG_T200_RUN, &st->l2.flag);
		st->ma.layer(st, MDL_ERROR | INDICATION, (void *) 'H');
		lapb_dl_release_l2l3(st, CONFIRM);
	} else {
		st->l2.rc++;
		FsmAddTimer(&st->l2.t200, st->l2.T200, EV_L2_T200,
			    NULL, 9);
		send_uframe(st, DISC | 0x10, CMD);
	}
}