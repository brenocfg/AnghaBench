#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union hv_synic_event_flags {int /*<<< orphan*/ * flags32; } ;
struct TYPE_3__ {scalar_t__ message_type; } ;
struct hv_message {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {void** synic_message_page; int /*<<< orphan*/ ** event_dpc; void** synic_event_page; } ;

/* Variables and functions */
 scalar_t__ HVMSG_NONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ VERSION_WIN7 ; 
 scalar_t__ VERSION_WS2008 ; 
 int VMBUS_MESSAGE_SINT ; 
 TYPE_2__ hv_context ; 
 int /*<<< orphan*/  msg_dpc ; 
 int smp_processor_id () ; 
 scalar_t__ sync_test_and_clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ vmbus_proto_version ; 

__attribute__((used)) static irqreturn_t vmbus_isr(int irq, void *dev_id)
{
	int cpu = smp_processor_id();
	void *page_addr;
	struct hv_message *msg;
	union hv_synic_event_flags *event;
	bool handled = false;

	page_addr = hv_context.synic_event_page[cpu];
	if (page_addr == NULL)
		return IRQ_NONE;

	event = (union hv_synic_event_flags *)page_addr +
					 VMBUS_MESSAGE_SINT;
	/*
	 * Check for events before checking for messages. This is the order
	 * in which events and messages are checked in Windows guests on
	 * Hyper-V, and the Windows team suggested we do the same.
	 */

	if ((vmbus_proto_version == VERSION_WS2008) ||
		(vmbus_proto_version == VERSION_WIN7)) {

		/* Since we are a child, we only need to check bit 0 */
		if (sync_test_and_clear_bit(0,
			(unsigned long *) &event->flags32[0])) {
			handled = true;
		}
	} else {
		/*
		 * Our host is win8 or above. The signaling mechanism
		 * has changed and we can directly look at the event page.
		 * If bit n is set then we have an interrup on the channel
		 * whose id is n.
		 */
		handled = true;
	}

	if (handled)
		tasklet_schedule(hv_context.event_dpc[cpu]);


	page_addr = hv_context.synic_message_page[cpu];
	msg = (struct hv_message *)page_addr + VMBUS_MESSAGE_SINT;

	/* Check if there are actual msgs to be processed */
	if (msg->header.message_type != HVMSG_NONE) {
		handled = true;
		tasklet_schedule(&msg_dpc);
	}

	if (handled)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}