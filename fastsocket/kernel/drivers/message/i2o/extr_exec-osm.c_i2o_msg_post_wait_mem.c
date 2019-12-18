#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {void* tcntxt; void* icntxt; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct i2o_message {TYPE_2__ u; } ;
struct i2o_dma {int /*<<< orphan*/ * virt; } ;
struct i2o_exec_wait {int /*<<< orphan*/  m; int /*<<< orphan*/  lock; TYPE_3__* msg; scalar_t__ complete; int /*<<< orphan*/ * wq; int /*<<< orphan*/  list; int /*<<< orphan*/  tcntxt; struct i2o_dma dma; } ;
struct i2o_controller {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  context; } ;
struct TYPE_7__ {int /*<<< orphan*/ * body; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 unsigned long HZ ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 TYPE_4__ i2o_exec_driver ; 
 struct i2o_exec_wait* i2o_exec_wait_alloc () ; 
 int /*<<< orphan*/  i2o_exec_wait_free (struct i2o_exec_wait*) ; 
 int /*<<< orphan*/  i2o_exec_wait_list ; 
 int /*<<< orphan*/  i2o_flush_reply (struct i2o_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2o_msg_nop (struct i2o_controller*,struct i2o_message*) ; 
 int /*<<< orphan*/  i2o_msg_post (struct i2o_controller*,struct i2o_message*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  wq ; 

int i2o_msg_post_wait_mem(struct i2o_controller *c, struct i2o_message *msg,
			  unsigned long timeout, struct i2o_dma *dma)
{
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	struct i2o_exec_wait *wait;
	static u32 tcntxt = 0x80000000;
	unsigned long flags;
	int rc = 0;

	wait = i2o_exec_wait_alloc();
	if (!wait) {
		i2o_msg_nop(c, msg);
		return -ENOMEM;
	}

	if (tcntxt == 0xffffffff)
		tcntxt = 0x80000000;

	if (dma)
		wait->dma = *dma;

	/*
	 * Fill in the message initiator context and transaction context.
	 * We will only use transaction contexts >= 0x80000000 for POST WAIT,
	 * so we could find a POST WAIT reply easier in the reply handler.
	 */
	msg->u.s.icntxt = cpu_to_le32(i2o_exec_driver.context);
	wait->tcntxt = tcntxt++;
	msg->u.s.tcntxt = cpu_to_le32(wait->tcntxt);

	wait->wq = &wq;
	/*
	 * we add elements to the head, because if a entry in the list will
	 * never be removed, we have to iterate over it every time
	 */
	list_add(&wait->list, &i2o_exec_wait_list);

	/*
	 * Post the message to the controller. At some point later it will
	 * return. If we time out before it returns then complete will be zero.
	 */
	i2o_msg_post(c, msg);

	wait_event_interruptible_timeout(wq, wait->complete, timeout * HZ);

	spin_lock_irqsave(&wait->lock, flags);

	wait->wq = NULL;

	if (wait->complete)
		rc = le32_to_cpu(wait->msg->body[0]) >> 24;
	else {
		/*
		 * We cannot remove it now. This is important. When it does
		 * terminate (which it must do if the controller has not
		 * died...) then it will otherwise scribble on stuff.
		 *
		 * FIXME: try abort message
		 */
		if (dma)
			dma->virt = NULL;

		rc = -ETIMEDOUT;
	}

	spin_unlock_irqrestore(&wait->lock, flags);

	if (rc != -ETIMEDOUT) {
		i2o_flush_reply(c, wait->m);
		i2o_exec_wait_free(wait);
	}

	return rc;
}