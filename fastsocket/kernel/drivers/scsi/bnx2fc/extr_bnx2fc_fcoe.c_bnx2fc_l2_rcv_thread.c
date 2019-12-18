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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fcoe_percpu_s {TYPE_1__ fcoe_rx_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  bnx2fc_recv_frame (struct sk_buff*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2fc_l2_rcv_thread(void *arg)
{
	struct fcoe_percpu_s *bg = arg;
	struct sk_buff *skb;

	set_user_nice(current, -20);
	set_current_state(TASK_INTERRUPTIBLE);
	while (!kthread_should_stop()) {
		schedule();
		spin_lock_bh(&bg->fcoe_rx_list.lock);
		while ((skb = __skb_dequeue(&bg->fcoe_rx_list)) != NULL) {
			spin_unlock_bh(&bg->fcoe_rx_list.lock);
			bnx2fc_recv_frame(skb);
			spin_lock_bh(&bg->fcoe_rx_list.lock);
		}
		__set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_bh(&bg->fcoe_rx_list.lock);
	}
	__set_current_state(TASK_RUNNING);
	return 0;
}