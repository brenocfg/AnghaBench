#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* sk_data_ready ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atm_force_charge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigd ; 
 int /*<<< orphan*/  sigd_sleep ; 
 TYPE_1__* sk_atm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void sigd_put_skb(struct sk_buff *skb)
{
#ifdef WAIT_FOR_DEMON
	DECLARE_WAITQUEUE(wait,current);

	add_wait_queue(&sigd_sleep,&wait);
	while (!sigd) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		pr_debug("atmsvc: waiting for signaling demon...\n");
		schedule();
	}
	current->state = TASK_RUNNING;
	remove_wait_queue(&sigd_sleep,&wait);
#else
	if (!sigd) {
		pr_debug("atmsvc: no signaling demon\n");
		kfree_skb(skb);
		return;
	}
#endif
	atm_force_charge(sigd,skb->truesize);
	skb_queue_tail(&sk_atm(sigd)->sk_receive_queue,skb);
	sk_atm(sigd)->sk_data_ready(sk_atm(sigd), skb->len);
}