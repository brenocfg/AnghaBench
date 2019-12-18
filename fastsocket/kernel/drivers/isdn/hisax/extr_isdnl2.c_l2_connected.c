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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ vs; scalar_t__ va; int /*<<< orphan*/  (* l2l1 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  i_queue; int /*<<< orphan*/  (* l2l3 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  T203; int /*<<< orphan*/  t203; scalar_t__ sow; scalar_t__ vr; int /*<<< orphan*/  flag; } ;
struct PStack {TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int CONFIRM ; 
 int DL_ESTABLISH ; 
 int /*<<< orphan*/  EV_L2_T203 ; 
 int /*<<< orphan*/  FLG_L3_INIT ; 
 int /*<<< orphan*/  FLG_PEND_REL ; 
 int /*<<< orphan*/  FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int INDICATION ; 
 int PH_PULL ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_L2_7 ; 
 scalar_t__ cansend (struct PStack*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  get_PollFlag (struct PStack*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2_disconnect (struct FsmInst*,int,void*) ; 
 int /*<<< orphan*/  l2_mdl_error_ua (struct FsmInst*,int,void*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_t200 (struct PStack*,int) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_connected(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;
	int pr=-1;

	if (!get_PollFlag(st, skb)) {
		l2_mdl_error_ua(fi, event, arg);
		return;
	}
	dev_kfree_skb(skb);

	if (test_and_clear_bit(FLG_PEND_REL, &st->l2.flag))
		l2_disconnect(fi, event, arg);

	if (test_and_clear_bit(FLG_L3_INIT, &st->l2.flag)) {
		pr = DL_ESTABLISH | CONFIRM;
	} else if (st->l2.vs != st->l2.va) {
		skb_queue_purge(&st->l2.i_queue);
		pr = DL_ESTABLISH | INDICATION;
	}

	stop_t200(st, 5);

	st->l2.vr = 0;
	st->l2.vs = 0;
	st->l2.va = 0;
	st->l2.sow = 0;
	FsmChangeState(fi, ST_L2_7);
	FsmAddTimer(&st->l2.t203, st->l2.T203, EV_L2_T203, NULL, 4);

	if (pr != -1)
		st->l2.l2l3(st, pr, NULL);

	if (!skb_queue_empty(&st->l2.i_queue) && cansend(st))
		st->l2.l2l1(st, PH_PULL | REQUEST, NULL);
}