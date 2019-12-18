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
struct sk_buff {int* data; } ;
struct Layer2 {unsigned int vs; unsigned int va; int /*<<< orphan*/  (* l2l1 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  i_queue; int /*<<< orphan*/  t203; int /*<<< orphan*/  T203; int /*<<< orphan*/  l2m; int /*<<< orphan*/  flag; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* layer ) (struct PStack*,int,void*) ;} ;
struct PStack {struct Layer2 l2; TYPE_1__ ma; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_L2_T203 ; 
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  FLG_ORIG ; 
 scalar_t__ FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmRestartTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int INDICATION ; 
 scalar_t__ IsREJ (int*,struct PStack*) ; 
 scalar_t__ IsRNR (int*,struct PStack*) ; 
 int MDL_ERROR ; 
 int PH_PULL ; 
 int REJ ; 
 int REQUEST ; 
 int RNR ; 
 int RR ; 
 int /*<<< orphan*/  clear_peer_busy (struct Layer2*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  enquiry_response (struct PStack*) ; 
 int /*<<< orphan*/  invoke_retransmission (struct PStack*,unsigned int) ; 
 int /*<<< orphan*/  l2addrsize (struct Layer2*) ; 
 int /*<<< orphan*/  l2m_debug (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ legalnr (struct PStack*,unsigned int) ; 
 int /*<<< orphan*/  nrerrorrecovery (struct FsmInst*) ; 
 int /*<<< orphan*/  restart_t200 (struct PStack*,int) ; 
 int /*<<< orphan*/  set_peer_busy (struct Layer2*) ; 
 int /*<<< orphan*/  setva (struct PStack*,unsigned int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_t200 (struct PStack*,int) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,void*) ; 
 int /*<<< orphan*/  stub2 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_st7_got_super(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;
	int PollFlag, rsp, typ = RR;
	unsigned int nr;
	struct Layer2 *l2 = &st->l2;

	rsp = *skb->data & 0x2;
	if (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;

	skb_pull(skb, l2addrsize(l2));
	if (IsRNR(skb->data, st)) {
		set_peer_busy(l2);
		typ = RNR;
	} else
		clear_peer_busy(l2);
	if (IsREJ(skb->data, st))
		typ = REJ;

	if (test_bit(FLG_MOD128, &l2->flag)) {
		PollFlag = (skb->data[1] & 0x1) == 0x1;
		nr = skb->data[1] >> 1;
	} else {
		PollFlag = (skb->data[0] & 0x10);
		nr = (skb->data[0] >> 5) & 0x7;
	}
	dev_kfree_skb(skb);

	if (PollFlag) {
		if (rsp)
			st->ma.layer(st, MDL_ERROR | INDICATION, (void *) 'A');
		else
			enquiry_response(st);
	}
	if (legalnr(st, nr)) {
		if (typ == REJ) {
			setva(st, nr);
			invoke_retransmission(st, nr);
			stop_t200(st, 10);
			if (FsmAddTimer(&st->l2.t203, st->l2.T203,
					EV_L2_T203, NULL, 6))
				l2m_debug(&st->l2.l2m, "Restart T203 ST7 REJ");
		} else if ((nr == l2->vs) && (typ == RR)) {
			setva(st, nr);
			stop_t200(st, 11);
			FsmRestartTimer(&st->l2.t203, st->l2.T203,
					EV_L2_T203, NULL, 7);
		} else if ((l2->va != nr) || (typ == RNR)) {
			setva(st, nr);
			if(typ != RR) FsmDelTimer(&st->l2.t203, 9);
			restart_t200(st, 12);
		}
		if (!skb_queue_empty(&st->l2.i_queue) && (typ == RR))
			st->l2.l2l1(st, PH_PULL | REQUEST, NULL);
	} else
		nrerrorrecovery(fi);
}