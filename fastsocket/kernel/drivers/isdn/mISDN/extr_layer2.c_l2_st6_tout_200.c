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
struct layer2 {scalar_t__ rc; scalar_t__ N200; int /*<<< orphan*/  T200; int /*<<< orphan*/  t200; scalar_t__ tm; int /*<<< orphan*/  flag; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int DISC ; 
 int /*<<< orphan*/  DL_RELEASE_CNF ; 
 int /*<<< orphan*/  EV_L2_T200 ; 
 int /*<<< orphan*/  FLG_DCHAN_BUSY ; 
 int /*<<< orphan*/  FLG_LAPD ; 
 int /*<<< orphan*/  FLG_T200_RUN ; 
 int /*<<< orphan*/  MDL_ERROR_IND ; 
 int /*<<< orphan*/  MDL_STATUS_DOWN_IND ; 
 int /*<<< orphan*/  ST_L2_4 ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2mgr (struct layer2*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lapb_dl_release_l2l3 (struct layer2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_uframe (struct layer2*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_st6_tout_200(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;

	if (test_bit(FLG_LAPD, &l2->flag) &&
		test_bit(FLG_DCHAN_BUSY, &l2->flag)) {
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200, NULL, 9);
	} else if (l2->rc == l2->N200) {
		mISDN_FsmChangeState(fi, ST_L2_4);
		test_and_clear_bit(FLG_T200_RUN, &l2->flag);
		l2mgr(l2, MDL_ERROR_IND, (void *) 'H');
		lapb_dl_release_l2l3(l2, DL_RELEASE_CNF);
		if (l2->tm)
			l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	} else {
		l2->rc++;
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200,
			    NULL, 9);
		send_uframe(l2, NULL, DISC | 0x10, CMD);
	}
}