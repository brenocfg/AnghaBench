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

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_backlog_wait ; 
 scalar_t__ audit_default ; 
 scalar_t__ audit_pid ; 
 int /*<<< orphan*/  audit_printk_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  audit_skb_hold_queue ; 
 int /*<<< orphan*/  audit_skb_queue ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kauditd_send_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kauditd_wait ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 scalar_t__ unlikely (struct sk_buff*) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kauditd_thread(void *dummy)
{
	struct sk_buff *skb;

	set_freezable();
	while (!kthread_should_stop()) {
		/*
		 * if auditd just started drain the queue of messages already
		 * sent to syslog/printk.  remember loss here is ok.  we already
		 * called audit_log_lost() if it didn't go out normally.  so the
		 * race between the skb_dequeue and the next check for audit_pid
		 * doesn't matter.
		 *
		 * if you ever find kauditd to be too slow we can get a perf win
		 * by doing our own locking and keeping better track if there
		 * are messages in this queue.  I don't see the need now, but
		 * in 5 years when I want to play with this again I'll see this
		 * note and still have no friggin idea what i'm thinking today.
		 */
		if (audit_default && audit_pid) {
			skb = skb_dequeue(&audit_skb_hold_queue);
			if (unlikely(skb)) {
				while (skb && audit_pid) {
					kauditd_send_skb(skb);
					skb = skb_dequeue(&audit_skb_hold_queue);
				}
			}
		}

		skb = skb_dequeue(&audit_skb_queue);
		wake_up(&audit_backlog_wait);
		if (skb) {
			if (audit_pid)
				kauditd_send_skb(skb);
			else
				audit_printk_skb(skb);
		} else {
			DECLARE_WAITQUEUE(wait, current);
			set_current_state(TASK_INTERRUPTIBLE);
			add_wait_queue(&kauditd_wait, &wait);

			if (!skb_queue_len(&audit_skb_queue)) {
				try_to_freeze();
				schedule();
			}

			__set_current_state(TASK_RUNNING);
			remove_wait_queue(&kauditd_wait, &wait);
		}
	}
	return 0;
}