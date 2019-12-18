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
struct onmessage_work_context {int /*<<< orphan*/  work; int /*<<< orphan*/  msg; } ;
struct TYPE_5__ {scalar_t__ msg_pending; } ;
struct TYPE_6__ {scalar_t__ message_type; TYPE_1__ message_flags; } ;
struct hv_message {TYPE_2__ header; } ;
struct TYPE_8__ {void** synic_message_page; } ;
struct TYPE_7__ {int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HVMSG_NONE ; 
 int /*<<< orphan*/  HV_X64_MSR_EOM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VMBUS_MESSAGE_SINT ; 
 TYPE_4__ hv_context ; 
 struct onmessage_work_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hv_message*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 TYPE_3__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_onmessage_work ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmbus_on_msg_dpc(unsigned long data)
{
	int cpu = smp_processor_id();
	void *page_addr = hv_context.synic_message_page[cpu];
	struct hv_message *msg = (struct hv_message *)page_addr +
				  VMBUS_MESSAGE_SINT;
	struct onmessage_work_context *ctx;

	while (1) {
		if (msg->header.message_type == HVMSG_NONE) {
			/* no msg */
			break;
		} else {
			ctx = kmalloc(sizeof(*ctx), GFP_ATOMIC);
			if (ctx == NULL)
				continue;
			INIT_WORK(&ctx->work, vmbus_onmessage_work);
			memcpy(&ctx->msg, msg, sizeof(*msg));
			queue_work(vmbus_connection.work_queue, &ctx->work);
		}

		msg->header.message_type = HVMSG_NONE;

		/*
		 * Make sure the write to MessageType (ie set to
		 * HVMSG_NONE) happens before we read the
		 * MessagePending and EOMing. Otherwise, the EOMing
		 * will not deliver any more messages since there is
		 * no empty slot
		 */
		mb();

		if (msg->header.message_flags.msg_pending) {
			/*
			 * This will cause message queue rescan to
			 * possibly deliver another msg from the
			 * hypervisor
			 */
			wrmsrl(HV_X64_MSR_EOM, 0);
		}
	}
}