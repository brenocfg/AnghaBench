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
struct sk_buff {int dummy; } ;
struct layer2 {scalar_t__ vs; scalar_t__ va; scalar_t__ tm; int /*<<< orphan*/  i_queue; int /*<<< orphan*/  T203; int /*<<< orphan*/  t203; scalar_t__ sow; scalar_t__ vr; int /*<<< orphan*/  flag; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int DL_ESTABLISH_CNF ; 
 int DL_ESTABLISH_IND ; 
 int /*<<< orphan*/  EV_L2_ACK_PULL ; 
 int /*<<< orphan*/  EV_L2_T203 ; 
 int /*<<< orphan*/  FLG_L3_INIT ; 
 int /*<<< orphan*/  FLG_PEND_REL ; 
 int /*<<< orphan*/  MDL_STATUS_UP_IND ; 
 int /*<<< orphan*/  ST_L2_7 ; 
 scalar_t__ cansend (struct layer2*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  get_PollFlag (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2_disconnect (struct FsmInst*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2_mdl_error_ua (struct FsmInst*,int,void*) ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2up_create (struct layer2*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmEvent (struct FsmInst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_t200 (struct layer2*,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_connected(struct FsmInst *fi, int event, void *arg)
{
	struct layer2	*l2 = fi->userdata;
	struct sk_buff	*skb = arg;
	int pr = -1;

	if (!get_PollFlag(l2, skb)) {
		l2_mdl_error_ua(fi, event, arg);
		return;
	}
	dev_kfree_skb(skb);
	if (test_and_clear_bit(FLG_PEND_REL, &l2->flag))
		l2_disconnect(fi, event, NULL);
	if (test_and_clear_bit(FLG_L3_INIT, &l2->flag)) {
		pr = DL_ESTABLISH_CNF;
	} else if (l2->vs != l2->va) {
		skb_queue_purge(&l2->i_queue);
		pr = DL_ESTABLISH_IND;
	}
	stop_t200(l2, 5);
	l2->vr = 0;
	l2->vs = 0;
	l2->va = 0;
	l2->sow = 0;
	mISDN_FsmChangeState(fi, ST_L2_7);
	mISDN_FsmAddTimer(&l2->t203, l2->T203, EV_L2_T203, NULL, 4);
	if (pr != -1)
		l2up_create(l2, pr, 0, NULL);

	if (skb_queue_len(&l2->i_queue) && cansend(l2))
		mISDN_FsmEvent(fi, EV_L2_ACK_PULL, NULL);

	if (l2->tm)
		l2_tei(l2, MDL_STATUS_UP_IND, 0);
}