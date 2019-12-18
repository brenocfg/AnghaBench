#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ status; int num_sections; int /*<<< orphan*/  sections; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; int /*<<< orphan*/  gpadl_handle; } ;
struct TYPE_10__ {TYPE_3__ send_recv_buf_complete; TYPE_2__ send_recv_buf; } ;
struct TYPE_11__ {TYPE_4__ v1_msg; } ;
struct TYPE_7__ {int /*<<< orphan*/  msg_type; } ;
struct nvsp_message {TYPE_5__ msg; TYPE_1__ hdr; } ;
struct nvsp_1_receive_buffer_section {int dummy; } ;
struct netvsc_device {scalar_t__ recv_buf_size; int recv_section_cnt; TYPE_6__* recv_section; int /*<<< orphan*/  channel_init_wait; int /*<<< orphan*/  recv_buf_gpadl_handle; struct nvsp_message channel_init_pkt; void* recv_buf; struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;
struct TYPE_12__ {scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  NETVSC_RECEIVE_BUFFER_ID ; 
 int /*<<< orphan*/  NVSP_MSG1_TYPE_SEND_RECV_BUF ; 
 scalar_t__ NVSP_STAT_SUCCESS ; 
 int /*<<< orphan*/  VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (scalar_t__) ; 
 struct netvsc_device* get_outbound_net_device (struct hv_device*) ; 
 TYPE_6__* kmemdup (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (struct nvsp_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netvsc_destroy_recv_buf (struct netvsc_device*) ; 
 int vmbus_establish_gpadl (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct nvsp_message*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int netvsc_init_recv_buf(struct hv_device *device)
{
	int ret = 0;
	int t;
	struct netvsc_device *net_device;
	struct nvsp_message *init_packet;
	struct net_device *ndev;

	net_device = get_outbound_net_device(device);
	if (!net_device)
		return -ENODEV;
	ndev = net_device->ndev;

	net_device->recv_buf =
		(void *)__get_free_pages(GFP_KERNEL|__GFP_ZERO,
				get_order(net_device->recv_buf_size));
	if (!net_device->recv_buf) {
		netdev_err(ndev, "unable to allocate receive "
			"buffer of size %d\n", net_device->recv_buf_size);
		ret = -ENOMEM;
		goto cleanup;
	}

	/*
	 * Establish the gpadl handle for this buffer on this
	 * channel.  Note: This call uses the vmbus connection rather
	 * than the channel to establish the gpadl handle.
	 */
	ret = vmbus_establish_gpadl(device->channel, net_device->recv_buf,
				    net_device->recv_buf_size,
				    &net_device->recv_buf_gpadl_handle);
	if (ret != 0) {
		netdev_err(ndev,
			"unable to establish receive buffer's gpadl\n");
		goto cleanup;
	}


	/* Notify the NetVsp of the gpadl handle */
	init_packet = &net_device->channel_init_pkt;

	memset(init_packet, 0, sizeof(struct nvsp_message));

	init_packet->hdr.msg_type = NVSP_MSG1_TYPE_SEND_RECV_BUF;
	init_packet->msg.v1_msg.send_recv_buf.
		gpadl_handle = net_device->recv_buf_gpadl_handle;
	init_packet->msg.v1_msg.
		send_recv_buf.id = NETVSC_RECEIVE_BUFFER_ID;

	/* Send the gpadl notification request */
	ret = vmbus_sendpacket(device->channel, init_packet,
			       sizeof(struct nvsp_message),
			       (unsigned long)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	if (ret != 0) {
		netdev_err(ndev,
			"unable to send receive buffer's gpadl to netvsp\n");
		goto cleanup;
	}

	t = wait_for_completion_timeout(&net_device->channel_init_wait, 5*HZ);
	BUG_ON(t == 0);


	/* Check the response */
	if (init_packet->msg.v1_msg.
	    send_recv_buf_complete.status != NVSP_STAT_SUCCESS) {
		netdev_err(ndev, "Unable to complete receive buffer "
			   "initialization with NetVsp - status %d\n",
			   init_packet->msg.v1_msg.
			   send_recv_buf_complete.status);
		ret = -EINVAL;
		goto cleanup;
	}

	/* Parse the response */

	net_device->recv_section_cnt = init_packet->msg.
		v1_msg.send_recv_buf_complete.num_sections;

	net_device->recv_section = kmemdup(
		init_packet->msg.v1_msg.send_recv_buf_complete.sections,
		net_device->recv_section_cnt *
		sizeof(struct nvsp_1_receive_buffer_section),
		GFP_KERNEL);
	if (net_device->recv_section == NULL) {
		ret = -EINVAL;
		goto cleanup;
	}

	/*
	 * For 1st release, there should only be 1 section that represents the
	 * entire receive buffer
	 */
	if (net_device->recv_section_cnt != 1 ||
	    net_device->recv_section->offset != 0) {
		ret = -EINVAL;
		goto cleanup;
	}

	goto exit;

cleanup:
	netvsc_destroy_recv_buf(net_device);

exit:
	return ret;
}