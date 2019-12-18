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
struct vmbus_channel_msginfo {int /*<<< orphan*/  waitevent; scalar_t__ msg; } ;
struct vmbus_channel_message_header {int /*<<< orphan*/  msgtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELMSG_REQUESTOFFERS ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmbus_channel_msginfo*) ; 
 struct vmbus_channel_msginfo* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int vmbus_post_msg (struct vmbus_channel_message_header*,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int vmbus_request_offers(void)
{
	struct vmbus_channel_message_header *msg;
	struct vmbus_channel_msginfo *msginfo;
	int ret, t;

	msginfo = kmalloc(sizeof(*msginfo) +
			  sizeof(struct vmbus_channel_message_header),
			  GFP_KERNEL);
	if (!msginfo)
		return -ENOMEM;

	init_completion(&msginfo->waitevent);

	msg = (struct vmbus_channel_message_header *)msginfo->msg;

	msg->msgtype = CHANNELMSG_REQUESTOFFERS;


	ret = vmbus_post_msg(msg,
			       sizeof(struct vmbus_channel_message_header));
	if (ret != 0) {
		pr_err("Unable to request offers - %d\n", ret);

		goto cleanup;
	}

	t = wait_for_completion_timeout(&msginfo->waitevent, 5*HZ);
	if (t == 0) {
		ret = -ETIMEDOUT;
		goto cleanup;
	}



cleanup:
	kfree(msginfo);

	return ret;
}