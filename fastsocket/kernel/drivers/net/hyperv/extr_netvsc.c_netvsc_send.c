#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
typedef  scalar_t__ u64 ;
struct TYPE_10__ {int channel_type; int send_buf_section_index; scalar_t__ send_buf_section_size; } ;
struct TYPE_11__ {TYPE_2__ send_rndis_pkt; } ;
struct TYPE_12__ {TYPE_3__ v1_msg; } ;
struct TYPE_9__ {int /*<<< orphan*/  msg_type; } ;
struct nvsp_message {TYPE_4__ msg; TYPE_1__ hdr; } ;
struct netvsc_device {int /*<<< orphan*/  num_outstanding_sends; struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct TYPE_13__ {scalar_t__ send_completion; } ;
struct TYPE_14__ {TYPE_5__ send; } ;
struct hv_netvsc_packet {scalar_t__ page_buf_cnt; int /*<<< orphan*/  page_buf; TYPE_6__ completion; scalar_t__ is_data_pkt; } ;
struct hv_device {TYPE_7__* channel; } ;
struct TYPE_15__ {int /*<<< orphan*/  outbound; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int ENOSPC ; 
 int /*<<< orphan*/  NVSP_MSG1_TYPE_SEND_RNDIS_PKT ; 
 scalar_t__ RING_AVAIL_PERCENT_LOWATER ; 
 int /*<<< orphan*/  VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct netvsc_device* get_outbound_net_device (struct hv_device*) ; 
 scalar_t__ hv_ringbuf_avail_percent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,struct hv_netvsc_packet*,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int vmbus_sendpacket (TYPE_7__*,struct nvsp_message*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmbus_sendpacket_pagebuffer (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__,struct nvsp_message*,int,scalar_t__) ; 

int netvsc_send(struct hv_device *device,
			struct hv_netvsc_packet *packet)
{
	struct netvsc_device *net_device;
	int ret = 0;
	struct nvsp_message sendMessage;
	struct net_device *ndev;
	u64 req_id;

	net_device = get_outbound_net_device(device);
	if (!net_device)
		return -ENODEV;
	ndev = net_device->ndev;

	sendMessage.hdr.msg_type = NVSP_MSG1_TYPE_SEND_RNDIS_PKT;
	if (packet->is_data_pkt) {
		/* 0 is RMC_DATA; */
		sendMessage.msg.v1_msg.send_rndis_pkt.channel_type = 0;
	} else {
		/* 1 is RMC_CONTROL; */
		sendMessage.msg.v1_msg.send_rndis_pkt.channel_type = 1;
	}

	/* Not using send buffer section */
	sendMessage.msg.v1_msg.send_rndis_pkt.send_buf_section_index =
		0xFFFFFFFF;
	sendMessage.msg.v1_msg.send_rndis_pkt.send_buf_section_size = 0;

	if (packet->completion.send.send_completion)
		req_id = (ulong)packet;
	else
		req_id = 0;

	if (packet->page_buf_cnt) {
		ret = vmbus_sendpacket_pagebuffer(device->channel,
						  packet->page_buf,
						  packet->page_buf_cnt,
						  &sendMessage,
						  sizeof(struct nvsp_message),
						  req_id);
	} else {
		ret = vmbus_sendpacket(device->channel, &sendMessage,
				sizeof(struct nvsp_message),
				req_id,
				VM_PKT_DATA_INBAND,
				VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	}

	if (ret == 0) {
		atomic_inc(&net_device->num_outstanding_sends);
		if (hv_ringbuf_avail_percent(&device->channel->outbound) <
			RING_AVAIL_PERCENT_LOWATER) {
			netif_stop_queue(ndev);
			if (atomic_read(&net_device->
				num_outstanding_sends) < 1)
				netif_wake_queue(ndev);
		}
	} else if (ret == -EAGAIN) {
		netif_stop_queue(ndev);
		if (atomic_read(&net_device->num_outstanding_sends) < 1) {
			netif_wake_queue(ndev);
			ret = -ENOSPC;
		}
	} else {
		netdev_err(ndev, "Unable to send packet %p ret %d\n",
			   packet, ret);
	}

	return ret;
}