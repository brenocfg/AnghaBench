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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  msgtype; } ;
struct vmbus_channel_close_channel {int /*<<< orphan*/  child_relid; TYPE_2__ header; } ;
struct TYPE_6__ {int /*<<< orphan*/  child_relid; } ;
struct TYPE_4__ {struct vmbus_channel_close_channel msg; } ;
struct vmbus_channel {int ringbuffer_pagecount; scalar_t__ ringbuffer_pages; scalar_t__ ringbuffer_gpadlhandle; TYPE_3__ offermsg; TYPE_1__ close_msg; int /*<<< orphan*/  inbound_lock; int /*<<< orphan*/ * onchannel_callback; int /*<<< orphan*/ * sc_creation_callback; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CHANNELMSG_CLOSECHANNEL ; 
 int /*<<< orphan*/  CHANNEL_OPEN_STATE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vmbus_post_msg (struct vmbus_channel_close_channel*,int) ; 
 int /*<<< orphan*/  vmbus_teardown_gpadl (struct vmbus_channel*,scalar_t__) ; 

__attribute__((used)) static void vmbus_close_internal(struct vmbus_channel *channel)
{
	struct vmbus_channel_close_channel *msg;
	int ret;
	unsigned long flags;

	channel->state = CHANNEL_OPEN_STATE;
	channel->sc_creation_callback = NULL;
	/* Stop callback and cancel the timer asap */
	spin_lock_irqsave(&channel->inbound_lock, flags);
	channel->onchannel_callback = NULL;
	spin_unlock_irqrestore(&channel->inbound_lock, flags);

	/* Send a closing message */

	msg = &channel->close_msg.msg;

	msg->header.msgtype = CHANNELMSG_CLOSECHANNEL;
	msg->child_relid = channel->offermsg.child_relid;

	ret = vmbus_post_msg(msg, sizeof(struct vmbus_channel_close_channel));

	BUG_ON(ret != 0);
	/* Tear down the gpadl for the channel's ring buffer */
	if (channel->ringbuffer_gpadlhandle)
		vmbus_teardown_gpadl(channel,
					  channel->ringbuffer_gpadlhandle);

	free_pages((unsigned long)channel->ringbuffer_pages,
		get_order(channel->ringbuffer_pagecount * PAGE_SIZE));


}