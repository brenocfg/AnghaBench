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
typedef  int u32 ;
struct spider_net_hw_descr {int data_status; int data_error; int /*<<< orphan*/  valid_size; } ;
struct spider_net_descr {struct sk_buff* skb; struct spider_net_hw_descr* hwdescr; } ;
struct TYPE_3__ {scalar_t__ rx_csum; } ;
struct spider_net_card {TYPE_1__ options; struct net_device* netdev; } ;
struct sk_buff {scalar_t__ len; void* ip_summed; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_2__ stats; } ;

/* Variables and functions */
 void* CHECKSUM_NONE ; 
 void* CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  SPIDER_MISALIGN ; 
 int SPIDER_NET_DATA_ERR_CKSUM_MASK ; 
 int SPIDER_NET_DATA_STATUS_CKSUM_MASK ; 
 int SPIDER_NET_VLAN_PACKET ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spider_net_pass_skb_up(struct spider_net_descr *descr,
		       struct spider_net_card *card)
{
	struct spider_net_hw_descr *hwdescr = descr->hwdescr;
	struct sk_buff *skb = descr->skb;
	struct net_device *netdev = card->netdev;
	u32 data_status = hwdescr->data_status;
	u32 data_error = hwdescr->data_error;

	skb_put(skb, hwdescr->valid_size);

	/* the card seems to add 2 bytes of junk in front
	 * of the ethernet frame */
#define SPIDER_MISALIGN		2
	skb_pull(skb, SPIDER_MISALIGN);
	skb->protocol = eth_type_trans(skb, netdev);

	/* checksum offload */
	if (card->options.rx_csum) {
		if ( ( (data_status & SPIDER_NET_DATA_STATUS_CKSUM_MASK) ==
		       SPIDER_NET_DATA_STATUS_CKSUM_MASK) &&
		     !(data_error & SPIDER_NET_DATA_ERR_CKSUM_MASK))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		else
			skb->ip_summed = CHECKSUM_NONE;
	} else
		skb->ip_summed = CHECKSUM_NONE;

	if (data_status & SPIDER_NET_VLAN_PACKET) {
		/* further enhancements: HW-accel VLAN
		 * vlan_hwaccel_receive_skb
		 */
	}

	/* update netdevice statistics */
	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += skb->len;

	/* pass skb up to stack */
	netif_receive_skb(skb);
}