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
struct sk_buff {int len; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  sk; TYPE_1__* dev; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct can_frame {int can_dlc; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_frames_delta; int /*<<< orphan*/  tx_frames; } ;
struct TYPE_3__ {scalar_t__ type; int flags; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  ETH_P_CAN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_ECHO ; 
 int IFF_UP ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  PACKET_LOOPBACK ; 
 TYPE_2__ can_stats ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int net_xmit_errno (int) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 

int can_send(struct sk_buff *skb, int loop)
{
	struct sk_buff *newskb = NULL;
	struct can_frame *cf = (struct can_frame *)skb->data;
	int err;

	if (skb->len != sizeof(struct can_frame) || cf->can_dlc > 8) {
		kfree_skb(skb);
		return -EINVAL;
	}

	if (skb->dev->type != ARPHRD_CAN) {
		kfree_skb(skb);
		return -EPERM;
	}

	if (!(skb->dev->flags & IFF_UP)) {
		kfree_skb(skb);
		return -ENETDOWN;
	}

	skb->protocol = htons(ETH_P_CAN);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	if (loop) {
		/* local loopback of sent CAN frames */

		/* indication for the CAN driver: do loopback */
		skb->pkt_type = PACKET_LOOPBACK;

		/*
		 * The reference to the originating sock may be required
		 * by the receiving socket to check whether the frame is
		 * its own. Example: can_raw sockopt CAN_RAW_RECV_OWN_MSGS
		 * Therefore we have to ensure that skb->sk remains the
		 * reference to the originating sock by restoring skb->sk
		 * after each skb_clone() or skb_orphan() usage.
		 */

		if (!(skb->dev->flags & IFF_ECHO)) {
			/*
			 * If the interface is not capable to do loopback
			 * itself, we do it here.
			 */
			newskb = skb_clone(skb, GFP_ATOMIC);
			if (!newskb) {
				kfree_skb(skb);
				return -ENOMEM;
			}

			newskb->sk = skb->sk;
			newskb->ip_summed = CHECKSUM_UNNECESSARY;
			newskb->pkt_type = PACKET_BROADCAST;
		}
	} else {
		/* indication for the CAN driver: no loopback required */
		skb->pkt_type = PACKET_HOST;
	}

	/* send to netdevice */
	err = dev_queue_xmit(skb);
	if (err > 0)
		err = net_xmit_errno(err);

	if (err) {
		kfree_skb(newskb);
		return err;
	}

	if (newskb)
		netif_rx_ni(newskb);

	/* update statistics */
	can_stats.tx_frames++;
	can_stats.tx_frames_delta++;

	return 0;
}