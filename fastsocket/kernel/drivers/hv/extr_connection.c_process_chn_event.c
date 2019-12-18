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
typedef  scalar_t__ u32 ;
struct vmbus_channel {int batched_reading; int /*<<< orphan*/  inbound_lock; int /*<<< orphan*/  inbound; int /*<<< orphan*/  (* onchannel_callback ) (void*) ;void* channel_callback_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  hv_begin_read (int /*<<< orphan*/ *) ; 
 scalar_t__ hv_end_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 struct vmbus_channel* relid2channel (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void process_chn_event(u32 relid)
{
	struct vmbus_channel *channel;
	unsigned long flags;
	void *arg;
	bool read_state;
	u32 bytes_to_read;

	/*
	 * Find the channel based on this relid and invokes the
	 * channel callback to process the event
	 */
	channel = relid2channel(relid);

	if (!channel) {
		pr_err("channel not found for relid - %u\n", relid);
		return;
	}

	/*
	 * A channel once created is persistent even when there
	 * is no driver handling the device. An unloading driver
	 * sets the onchannel_callback to NULL under the
	 * protection of the channel inbound_lock. Thus, checking
	 * and invoking the driver specific callback takes care of
	 * orderly unloading of the driver.
	 */

	spin_lock_irqsave(&channel->inbound_lock, flags);
	if (channel->onchannel_callback != NULL) {
		arg = channel->channel_callback_context;
		read_state = channel->batched_reading;
		/*
		 * This callback reads the messages sent by the host.
		 * We can optimize host to guest signaling by ensuring:
		 * 1. While reading the channel, we disable interrupts from
		 *    host.
		 * 2. Ensure that we process all posted messages from the host
		 *    before returning from this callback.
		 * 3. Once we return, enable signaling from the host. Once this
		 *    state is set we check to see if additional packets are
		 *    available to read. In this case we repeat the process.
		 */

		do {
			hv_begin_read(&channel->inbound);
			channel->onchannel_callback(arg);
			bytes_to_read = hv_end_read(&channel->inbound);
		} while (read_state && (bytes_to_read != 0));
	} else {
		pr_err("no channel callback for relid - %u\n", relid);
	}

	spin_unlock_irqrestore(&channel->inbound_lock, flags);
}