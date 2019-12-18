#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct packet_task {scalar_t__ tx_type; struct hpsb_packet* packet; TYPE_1__* skb; int /*<<< orphan*/  addr; int /*<<< orphan*/  dest_node; struct eth1394_priv* priv; } ;
struct hpsb_packet {int dummy; } ;
struct eth1394_priv {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  quadlet_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ ETH1394_GASP ; 
 struct hpsb_packet* ether1394_alloc_common_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether1394_complete_cb ; 
 int /*<<< orphan*/  ether1394_free_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  ether1394_prep_gasp_packet (struct hpsb_packet*,struct eth1394_priv*,TYPE_1__*,int) ; 
 scalar_t__ ether1394_prep_write_packet (struct hpsb_packet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hpsb_free_packet (struct hpsb_packet*) ; 
 scalar_t__ hpsb_send_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  hpsb_set_packet_complete_task (struct hpsb_packet*,int /*<<< orphan*/ ,struct packet_task*) ; 

__attribute__((used)) static int ether1394_send_packet(struct packet_task *ptask, unsigned int tx_len)
{
	struct eth1394_priv *priv = ptask->priv;
	struct hpsb_packet *packet = NULL;

	packet = ether1394_alloc_common_packet(priv->host);
	if (!packet)
		return -ENOMEM;

	if (ptask->tx_type == ETH1394_GASP) {
		int length = tx_len + 2 * sizeof(quadlet_t);

		ether1394_prep_gasp_packet(packet, priv, ptask->skb, length);
	} else if (ether1394_prep_write_packet(packet, priv->host,
					       ptask->dest_node,
					       ptask->addr, ptask->skb->data,
					       tx_len)) {
		hpsb_free_packet(packet);
		return -EAGAIN;
	}

	ptask->packet = packet;
	hpsb_set_packet_complete_task(ptask->packet, ether1394_complete_cb,
				      ptask);

	if (hpsb_send_packet(packet) < 0) {
		ether1394_free_packet(packet);
		return -EIO;
	}

	return 0;
}