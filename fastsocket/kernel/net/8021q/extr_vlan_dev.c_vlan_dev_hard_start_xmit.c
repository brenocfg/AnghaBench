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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_ethhdr {scalar_t__ h_vlan_proto; } ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct netdev_queue {unsigned int tx_bytes; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  real_dev; int /*<<< orphan*/  cnt_inc_headroom_on_tx; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  cnt_encap_on_xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int NET_XMIT_SUCCESS ; 
 int VLAN_FLAG_REORDER_HDR ; 
 unsigned int VLAN_HLEN ; 
 struct sk_buff* __vlan_put_tag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_dev_get_egress_qos_mask (struct net_device*,struct sk_buff*) ; 
 TYPE_1__* vlan_dev_info (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t vlan_dev_hard_start_xmit(struct sk_buff *skb,
					    struct net_device *dev)
{
	int i = skb_get_queue_mapping(skb);
	struct netdev_queue *txq = netdev_get_tx_queue(dev, i);
	struct vlan_ethhdr *veth = (struct vlan_ethhdr *)(skb->data);
	unsigned int len;
	int ret;

	/* Handle non-VLAN frames if they are sent to us, for example by DHCP.
	 *
	 * NOTE: THIS ASSUMES DIX ETHERNET, SPECIFICALLY NOT SUPPORTING
	 * OTHER THINGS LIKE FDDI/TokenRing/802.3 SNAPs...
	 */
	if (veth->h_vlan_proto != htons(ETH_P_8021Q) ||
	    vlan_dev_info(dev)->flags & VLAN_FLAG_REORDER_HDR) {
		unsigned int orig_headroom = skb_headroom(skb);
		u16 vlan_tci;

		vlan_dev_info(dev)->cnt_encap_on_xmit++;

		vlan_tci = vlan_dev_info(dev)->vlan_id;
		vlan_tci |= vlan_dev_get_egress_qos_mask(dev, skb);
		skb = __vlan_put_tag(skb, vlan_tci);
		if (!skb) {
			txq->tx_dropped++;
			return NETDEV_TX_OK;
		}

		if (orig_headroom < VLAN_HLEN)
			vlan_dev_info(dev)->cnt_inc_headroom_on_tx++;
	}


	skb->dev = vlan_dev_info(dev)->real_dev;
	len = skb->len;
	ret = dev_queue_xmit(skb);

	if (likely(ret == NET_XMIT_SUCCESS)) {
		txq->tx_packets++;
		txq->tx_bytes += len;
	} else
		txq->tx_dropped++;

	return NETDEV_TX_OK;
}