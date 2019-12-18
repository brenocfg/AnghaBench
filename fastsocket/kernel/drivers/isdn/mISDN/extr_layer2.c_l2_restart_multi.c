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
struct layer2 {scalar_t__ vs; scalar_t__ va; int /*<<< orphan*/  i_queue; int /*<<< orphan*/  T203; int /*<<< orphan*/  t203; scalar_t__ sow; scalar_t__ vr; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_ESTABLISH_IND ; 
 int /*<<< orphan*/  EV_L2_ACK_PULL ; 
 int /*<<< orphan*/  EV_L2_T203 ; 
 int /*<<< orphan*/  MDL_ERROR_IND ; 
 int /*<<< orphan*/  RSP ; 
 int /*<<< orphan*/  ST_L2_7 ; 
 int UA ; 
 scalar_t__ cansend (struct layer2*) ; 
 int /*<<< orphan*/  clear_exception (struct layer2*) ; 
 int get_PollFlag (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2mgr (struct layer2*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2up_create (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmEvent (struct FsmInst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_FsmRestartTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_uframe (struct layer2*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_t200 (struct layer2*,int) ; 

__attribute__((used)) static void
l2_restart_multi(struct FsmInst *fi, int event, void *arg)
{
	struct layer2	*l2 = fi->userdata;
	struct sk_buff	*skb = arg;
	int		est = 0;

	send_uframe(l2, skb, UA | get_PollFlag(l2, skb), RSP);

	l2mgr(l2, MDL_ERROR_IND, (void *) 'F');

	if (l2->vs != l2->va) {
		skb_queue_purge(&l2->i_queue);
		est = 1;
	}

	clear_exception(l2);
	l2->vs = 0;
	l2->va = 0;
	l2->vr = 0;
	l2->sow = 0;
	mISDN_FsmChangeState(fi, ST_L2_7);
	stop_t200(l2, 3);
	mISDN_FsmRestartTimer(&l2->t203, l2->T203, EV_L2_T203, NULL, 3);

	if (est)
		l2up_create(l2, DL_ESTABLISH_IND, 0, NULL);
/*		mISDN_queue_data(&l2->inst, l2->inst.id | MSG_BROADCAST,
 *		    MGR_SHORTSTATUS | INDICATION, SSTATUS_L2_ESTABLISHED,
 *		    0, NULL, 0);
 */
	if (skb_queue_len(&l2->i_queue) && cansend(l2))
		mISDN_FsmEvent(fi, EV_L2_ACK_PULL, NULL);
}