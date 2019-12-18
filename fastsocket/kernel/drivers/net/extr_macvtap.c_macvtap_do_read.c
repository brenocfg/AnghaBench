#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk_sleep; int /*<<< orphan*/  sk_receive_queue; } ;
struct macvtap_queue {TYPE_1__ sk; } ;
struct kiocb {int dummy; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  macvtap_put_user (struct macvtap_queue*,struct sk_buff*,struct iovec const*,unsigned long) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (TYPE_2__*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static ssize_t macvtap_do_read(struct macvtap_queue *q, struct kiocb *iocb,
			       const struct iovec *iv, unsigned long len,
			       int noblock)
{
	DECLARE_WAITQUEUE(wait, current);
	struct sk_buff *skb;
	ssize_t ret = 0;

	add_wait_queue(q->sk.sk_sleep, &wait);
	while (len) {
		current->state = TASK_INTERRUPTIBLE;

		/* Read frames from the queue */
		skb = skb_dequeue(&q->sk.sk_receive_queue);
		if (!skb) {
			if (noblock) {
				ret = -EAGAIN;
				break;
			}
			if (signal_pending(current)) {
				ret = -ERESTARTSYS;
				break;
			}
			/* Nothing to read, let's sleep */
			schedule();
			continue;
		}
		ret = macvtap_put_user(q, skb, iv, len);
		kfree_skb(skb);
		break;
	}

	current->state = TASK_RUNNING;
	remove_wait_queue(q->sk.sk_sleep, &wait);
	return ret;
}