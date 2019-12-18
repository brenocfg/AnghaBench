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
struct vmbus_channel_rescind_offer {int /*<<< orphan*/  child_relid; } ;
struct vmbus_channel_message_header {int dummy; } ;
struct vmbus_channel {int /*<<< orphan*/  work; int /*<<< orphan*/  controlwq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vmbus_channel* relid2channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmbus_onoffer_rescind(struct vmbus_channel_message_header *hdr)
{
	struct vmbus_channel_rescind_offer *rescind;
	struct vmbus_channel *channel;

	rescind = (struct vmbus_channel_rescind_offer *)hdr;
	channel = relid2channel(rescind->child_relid);

	if (channel == NULL)
		/* Just return here, no channel found */
		return;

	/* work is initialized for vmbus_process_rescind_offer() from
	 * vmbus_process_offer() where the channel got created */
	queue_work(channel->controlwq, &channel->work);
}