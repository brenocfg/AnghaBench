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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct netvsc_device {int /*<<< orphan*/  recv_pkt_list_lock; int /*<<< orphan*/  recv_pkt_list; struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  recv_completion_tid; } ;
struct TYPE_5__ {TYPE_1__ recv; } ;
struct hv_netvsc_packet {scalar_t__ status; int /*<<< orphan*/  list_ent; TYPE_3__* xfer_page_pkt; TYPE_2__ completion; struct hv_device* device; } ;
struct hv_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ count; int /*<<< orphan*/  list_ent; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVSP_STAT_FAIL ; 
 int /*<<< orphan*/  NVSP_STAT_NONE ; 
 scalar_t__ NVSP_STAT_SUCCESS ; 
 struct netvsc_device* get_inbound_net_device (struct hv_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netvsc_send_recv_completion (struct hv_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void netvsc_receive_completion(void *context)
{
	struct hv_netvsc_packet *packet = context;
	struct hv_device *device = packet->device;
	struct netvsc_device *net_device;
	u64 transaction_id = 0;
	bool fsend_receive_comp = false;
	unsigned long flags;
	struct net_device *ndev;
	u32 status = NVSP_STAT_NONE;

	/*
	 * Even though it seems logical to do a GetOutboundNetDevice() here to
	 * send out receive completion, we are using GetInboundNetDevice()
	 * since we may have disable outbound traffic already.
	 */
	net_device = get_inbound_net_device(device);
	if (!net_device)
		return;
	ndev = net_device->ndev;

	/* Overloading use of the lock. */
	spin_lock_irqsave(&net_device->recv_pkt_list_lock, flags);

	if (packet->status != NVSP_STAT_SUCCESS)
		packet->xfer_page_pkt->status = NVSP_STAT_FAIL;

	packet->xfer_page_pkt->count--;

	/*
	 * Last one in the line that represent 1 xfer page packet.
	 * Return the xfer page packet itself to the freelist
	 */
	if (packet->xfer_page_pkt->count == 0) {
		fsend_receive_comp = true;
		transaction_id = packet->completion.recv.recv_completion_tid;
		status = packet->xfer_page_pkt->status;
		list_add_tail(&packet->xfer_page_pkt->list_ent,
			      &net_device->recv_pkt_list);

	}

	/* Put the packet back */
	list_add_tail(&packet->list_ent, &net_device->recv_pkt_list);
	spin_unlock_irqrestore(&net_device->recv_pkt_list_lock, flags);

	/* Send a receive completion for the xfer page packet */
	if (fsend_receive_comp)
		netvsc_send_recv_completion(device, transaction_id, status);

}