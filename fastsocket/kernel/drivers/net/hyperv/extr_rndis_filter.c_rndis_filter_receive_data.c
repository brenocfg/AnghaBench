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
typedef  scalar_t__ u32 ;
struct rndis_packet {scalar_t__ data_offset; scalar_t__ data_len; } ;
struct TYPE_3__ {struct rndis_packet pkt; } ;
struct rndis_message {TYPE_1__ msg; } ;
struct rndis_device {TYPE_2__* net_dev; } ;
struct ndis_pkt_8021q_info {int vlanid; int pri; } ;
struct hv_netvsc_packet {scalar_t__ total_data_buflen; int is_data_pkt; int vlan_tci; void* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE_8021Q_INFO ; 
 scalar_t__ RNDIS_HEADER_SIZE ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_TAG_PRESENT ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  netvsc_recv_callback (int /*<<< orphan*/ ,struct hv_netvsc_packet*) ; 
 struct ndis_pkt_8021q_info* rndis_get_ppi (struct rndis_packet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rndis_filter_receive_data(struct rndis_device *dev,
				   struct rndis_message *msg,
				   struct hv_netvsc_packet *pkt)
{
	struct rndis_packet *rndis_pkt;
	u32 data_offset;
	struct ndis_pkt_8021q_info *vlan;

	rndis_pkt = &msg->msg.pkt;

	/* Remove the rndis header and pass it back up the stack */
	data_offset = RNDIS_HEADER_SIZE + rndis_pkt->data_offset;

	pkt->total_data_buflen -= data_offset;

	/*
	 * Make sure we got a valid RNDIS message, now total_data_buflen
	 * should be the data packet size plus the trailer padding size
	 */
	if (pkt->total_data_buflen < rndis_pkt->data_len) {
		netdev_err(dev->net_dev->ndev, "rndis message buffer "
			   "overflow detected (got %u, min %u)"
			   "...dropping this message!\n",
			   pkt->total_data_buflen, rndis_pkt->data_len);
		return;
	}

	/*
	 * Remove the rndis trailer padding from rndis packet message
	 * rndis_pkt->data_len tell us the real data length, we only copy
	 * the data packet to the stack, without the rndis trailer padding
	 */
	pkt->total_data_buflen = rndis_pkt->data_len;
	pkt->data = (void *)((unsigned long)pkt->data + data_offset);

	pkt->is_data_pkt = true;

	vlan = rndis_get_ppi(rndis_pkt, IEEE_8021Q_INFO);
	if (vlan) {
		pkt->vlan_tci = VLAN_TAG_PRESENT | vlan->vlanid |
			(vlan->pri << VLAN_PRIO_SHIFT);
	} else {
		pkt->vlan_tci = 0;
	}

	netvsc_recv_callback(dev->net_dev->dev, pkt);
}