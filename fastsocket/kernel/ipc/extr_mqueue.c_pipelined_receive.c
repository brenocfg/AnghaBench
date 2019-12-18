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
struct mqueue_inode_info {int /*<<< orphan*/  wait_q; } ;
struct ext_wait_queue {int /*<<< orphan*/  state; int /*<<< orphan*/  task; int /*<<< orphan*/  list; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND ; 
 int /*<<< orphan*/  STATE_PENDING ; 
 int /*<<< orphan*/  STATE_READY ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ msg_insert (int /*<<< orphan*/ ,struct mqueue_inode_info*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 struct ext_wait_queue* wq_get_first_waiter (struct mqueue_inode_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pipelined_receive(struct mqueue_inode_info *info)
{
	struct ext_wait_queue *sender = wq_get_first_waiter(info, SEND);

	if (!sender) {
		/* for poll */
		wake_up_interruptible(&info->wait_q);
		return;
	}
	if (msg_insert(sender->msg, info))
		return;
	list_del(&sender->list);
	sender->state = STATE_PENDING;
	wake_up_process(sender->task);
	smp_wmb();
	sender->state = STATE_READY;
}