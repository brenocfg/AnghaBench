#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct xferpage_packet {int count; void* status; int /*<<< orphan*/  list_ent; } ;
struct TYPE_11__ {int /*<<< orphan*/  trans_id; } ;
struct vmtransfer_page_packet_header {scalar_t__ xfer_pageset_id; int range_cnt; TYPE_3__* ranges; TYPE_2__ d; } ;
struct vmpacket_descriptor {int offset8; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {scalar_t__ msg_type; } ;
struct nvsp_message {TYPE_1__ hdr; } ;
struct TYPE_15__ {scalar_t__ next; } ;
struct netvsc_device {scalar_t__ recv_buf; int /*<<< orphan*/  recv_pkt_list_lock; TYPE_6__ recv_pkt_list; struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct TYPE_13__ {struct hv_netvsc_packet* recv_completion_ctx; int /*<<< orphan*/  recv_completion_tid; int /*<<< orphan*/  (* recv_completion ) (struct hv_netvsc_packet*) ;} ;
struct TYPE_14__ {TYPE_4__ recv; } ;
struct hv_netvsc_packet {TYPE_5__ completion; int /*<<< orphan*/  total_data_buflen; void* data; struct hv_device* device; struct xferpage_packet* xfer_page_pkt; void* status; int /*<<< orphan*/  list_ent; } ;
struct hv_device {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  byte_count; scalar_t__ byte_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (TYPE_6__) ; 
 scalar_t__ NETVSC_RECEIVE_BUFFER_ID ; 
 scalar_t__ NVSP_MSG1_TYPE_SEND_RNDIS_PKT ; 
 int /*<<< orphan*/  NVSP_STAT_FAIL ; 
 void* NVSP_STAT_SUCCESS ; 
 int /*<<< orphan*/  VM_PKT_DATA_USING_XFER_PAGES ; 
 struct netvsc_device* get_inbound_net_device (struct hv_device*) ; 
 TYPE_6__ listHead ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_6__*) ; 
 int /*<<< orphan*/  list_move_tail (scalar_t__,TYPE_6__*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,...) ; 
 int /*<<< orphan*/  netvsc_receive_completion (struct hv_netvsc_packet*) ; 
 int /*<<< orphan*/  netvsc_send_recv_completion (struct hv_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndis_filter_receive (struct hv_device*,struct hv_netvsc_packet*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void netvsc_receive(struct hv_device *device,
			    struct vmpacket_descriptor *packet)
{
	struct netvsc_device *net_device;
	struct vmtransfer_page_packet_header *vmxferpage_packet;
	struct nvsp_message *nvsp_packet;
	struct hv_netvsc_packet *netvsc_packet = NULL;
	/* struct netvsc_driver *netvscDriver; */
	struct xferpage_packet *xferpage_packet = NULL;
	int i;
	int count = 0;
	unsigned long flags;
	struct net_device *ndev;

	LIST_HEAD(listHead);

	net_device = get_inbound_net_device(device);
	if (!net_device)
		return;
	ndev = net_device->ndev;

	/*
	 * All inbound packets other than send completion should be xfer page
	 * packet
	 */
	if (packet->type != VM_PKT_DATA_USING_XFER_PAGES) {
		netdev_err(ndev, "Unknown packet type received - %d\n",
			   packet->type);
		return;
	}

	nvsp_packet = (struct nvsp_message *)((unsigned long)packet +
			(packet->offset8 << 3));

	/* Make sure this is a valid nvsp packet */
	if (nvsp_packet->hdr.msg_type !=
	    NVSP_MSG1_TYPE_SEND_RNDIS_PKT) {
		netdev_err(ndev, "Unknown nvsp packet type received-"
			" %d\n", nvsp_packet->hdr.msg_type);
		return;
	}

	vmxferpage_packet = (struct vmtransfer_page_packet_header *)packet;

	if (vmxferpage_packet->xfer_pageset_id != NETVSC_RECEIVE_BUFFER_ID) {
		netdev_err(ndev, "Invalid xfer page set id - "
			   "expecting %x got %x\n", NETVSC_RECEIVE_BUFFER_ID,
			   vmxferpage_packet->xfer_pageset_id);
		return;
	}

	/*
	 * Grab free packets (range count + 1) to represent this xfer
	 * page packet. +1 to represent the xfer page packet itself.
	 * We grab it here so that we know exactly how many we can
	 * fulfil
	 */
	spin_lock_irqsave(&net_device->recv_pkt_list_lock, flags);
	while (!list_empty(&net_device->recv_pkt_list)) {
		list_move_tail(net_device->recv_pkt_list.next, &listHead);
		if (++count == vmxferpage_packet->range_cnt + 1)
			break;
	}
	spin_unlock_irqrestore(&net_device->recv_pkt_list_lock, flags);

	/*
	 * We need at least 2 netvsc pkts (1 to represent the xfer
	 * page and at least 1 for the range) i.e. we can handled
	 * some of the xfer page packet ranges...
	 */
	if (count < 2) {
		netdev_err(ndev, "Got only %d netvsc pkt...needed "
			"%d pkts. Dropping this xfer page packet completely!\n",
			count, vmxferpage_packet->range_cnt + 1);

		/* Return it to the freelist */
		spin_lock_irqsave(&net_device->recv_pkt_list_lock, flags);
		for (i = count; i != 0; i--) {
			list_move_tail(listHead.next,
				       &net_device->recv_pkt_list);
		}
		spin_unlock_irqrestore(&net_device->recv_pkt_list_lock,
				       flags);

		netvsc_send_recv_completion(device,
					    vmxferpage_packet->d.trans_id,
					    NVSP_STAT_FAIL);

		return;
	}

	/* Remove the 1st packet to represent the xfer page packet itself */
	xferpage_packet = (struct xferpage_packet *)listHead.next;
	list_del(&xferpage_packet->list_ent);
	xferpage_packet->status = NVSP_STAT_SUCCESS;

	/* This is how much we can satisfy */
	xferpage_packet->count = count - 1;

	if (xferpage_packet->count != vmxferpage_packet->range_cnt) {
		netdev_err(ndev, "Needed %d netvsc pkts to satisfy "
			"this xfer page...got %d\n",
			vmxferpage_packet->range_cnt, xferpage_packet->count);
	}

	/* Each range represents 1 RNDIS pkt that contains 1 ethernet frame */
	for (i = 0; i < (count - 1); i++) {
		netvsc_packet = (struct hv_netvsc_packet *)listHead.next;
		list_del(&netvsc_packet->list_ent);

		/* Initialize the netvsc packet */
		netvsc_packet->status = NVSP_STAT_SUCCESS;
		netvsc_packet->xfer_page_pkt = xferpage_packet;
		netvsc_packet->completion.recv.recv_completion =
					netvsc_receive_completion;
		netvsc_packet->completion.recv.recv_completion_ctx =
					netvsc_packet;
		netvsc_packet->device = device;
		/* Save this so that we can send it back */
		netvsc_packet->completion.recv.recv_completion_tid =
					vmxferpage_packet->d.trans_id;

		netvsc_packet->data = (void *)((unsigned long)net_device->
			recv_buf + vmxferpage_packet->ranges[i].byte_offset);
		netvsc_packet->total_data_buflen =
					vmxferpage_packet->ranges[i].byte_count;

		/* Pass it to the upper layer */
		rndis_filter_receive(device, netvsc_packet);

		netvsc_receive_completion(netvsc_packet->
				completion.recv.recv_completion_ctx);
	}

}