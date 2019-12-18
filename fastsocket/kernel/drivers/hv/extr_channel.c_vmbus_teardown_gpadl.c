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
typedef  int /*<<< orphan*/  u32 ;
struct vmbus_channel_msginfo {int /*<<< orphan*/  msglistentry; int /*<<< orphan*/  waitevent; scalar_t__ msg; } ;
struct TYPE_4__ {int /*<<< orphan*/  msgtype; } ;
struct vmbus_channel_gpadl_teardown {int /*<<< orphan*/  gpadl; int /*<<< orphan*/  child_relid; TYPE_1__ header; } ;
struct TYPE_5__ {int /*<<< orphan*/  child_relid; } ;
struct vmbus_channel {TYPE_2__ offermsg; } ;
struct TYPE_6__ {int /*<<< orphan*/  channelmsg_lock; int /*<<< orphan*/  chn_msg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CHANNELMSG_GPADL_TEARDOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmbus_channel_msginfo*) ; 
 struct vmbus_channel_msginfo* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_3__ vmbus_connection ; 
 int vmbus_post_msg (struct vmbus_channel_gpadl_teardown*,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int vmbus_teardown_gpadl(struct vmbus_channel *channel, u32 gpadl_handle)
{
	struct vmbus_channel_gpadl_teardown *msg;
	struct vmbus_channel_msginfo *info;
	unsigned long flags;
	int ret, t;

	info = kmalloc(sizeof(*info) +
		       sizeof(struct vmbus_channel_gpadl_teardown), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	init_completion(&info->waitevent);

	msg = (struct vmbus_channel_gpadl_teardown *)info->msg;

	msg->header.msgtype = CHANNELMSG_GPADL_TEARDOWN;
	msg->child_relid = channel->offermsg.child_relid;
	msg->gpadl = gpadl_handle;

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_add_tail(&info->msglistentry,
		      &vmbus_connection.chn_msg_list);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
	ret = vmbus_post_msg(msg,
			       sizeof(struct vmbus_channel_gpadl_teardown));

	BUG_ON(ret != 0);
	t = wait_for_completion_timeout(&info->waitevent, 5*HZ);
	BUG_ON(t == 0);

	/* Received a torndown response */
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_del(&info->msglistentry);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	kfree(info);
	return ret;
}