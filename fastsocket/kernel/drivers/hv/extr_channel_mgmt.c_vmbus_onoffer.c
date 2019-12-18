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
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  if_type; } ;
struct vmbus_channel_offer_channel {scalar_t__ is_dedicated_interrupt; scalar_t__ monitorid; TYPE_3__ offer; int /*<<< orphan*/  connection_id; } ;
struct vmbus_channel_message_header {int dummy; } ;
struct vmbus_channel {int batched_reading; int is_dedicated_interrupt; int monitor_grp; int monitor_bit; int /*<<< orphan*/  work; int /*<<< orphan*/  controlwq; int /*<<< orphan*/  offermsg; int /*<<< orphan*/  target_vp; struct hv_input_signal_event* sig_event; int /*<<< orphan*/  sig_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ u; scalar_t__ asu32; } ;
struct hv_input_signal_event {TYPE_2__ connectionid; scalar_t__ rsvdz; scalar_t__ flag_number; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HV_HYPERCALL_PARAM_ALIGN ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ VERSION_WS2008 ; 
 int /*<<< orphan*/  VMBUS_EVENT_CONNECTION_ID ; 
 struct vmbus_channel* alloc_channel () ; 
 int /*<<< orphan*/  get_vp_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct vmbus_channel_offer_channel*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_process_offer ; 
 scalar_t__ vmbus_proto_version ; 

__attribute__((used)) static void vmbus_onoffer(struct vmbus_channel_message_header *hdr)
{
	struct vmbus_channel_offer_channel *offer;
	struct vmbus_channel *newchannel;

	offer = (struct vmbus_channel_offer_channel *)hdr;

	/* Allocate the channel object and save this offer. */
	newchannel = alloc_channel();
	if (!newchannel) {
		pr_err("Unable to allocate channel object\n");
		return;
	}

	/*
	 * By default we setup state to enable batched
	 * reading. A specific service can choose to
	 * disable this prior to opening the channel.
	 */
	newchannel->batched_reading = true;

	/*
	 * Setup state for signalling the host.
	 */
	newchannel->sig_event = (struct hv_input_signal_event *)
				(ALIGN((unsigned long)
				&newchannel->sig_buf,
				HV_HYPERCALL_PARAM_ALIGN));

	newchannel->sig_event->connectionid.asu32 = 0;
	newchannel->sig_event->connectionid.u.id = VMBUS_EVENT_CONNECTION_ID;
	newchannel->sig_event->flag_number = 0;
	newchannel->sig_event->rsvdz = 0;

	if (vmbus_proto_version != VERSION_WS2008) {
		newchannel->is_dedicated_interrupt =
				(offer->is_dedicated_interrupt != 0);
		newchannel->sig_event->connectionid.u.id =
				offer->connection_id;
	}

	newchannel->target_vp = get_vp_index(&offer->offer.if_type);

	memcpy(&newchannel->offermsg, offer,
	       sizeof(struct vmbus_channel_offer_channel));
	newchannel->monitor_grp = (u8)offer->monitorid / 32;
	newchannel->monitor_bit = (u8)offer->monitorid % 32;

	INIT_WORK(&newchannel->work, vmbus_process_offer);
	queue_work(newchannel->controlwq, &newchannel->work);
}