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
struct TYPE_5__ {int /*<<< orphan*/  lp; } ;
struct vnet_port {TYPE_2__ vio; TYPE_1__* vp; } ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {TYPE_3__ stats; } ;
struct ldc_trans_cookie {int dummy; } ;
struct TYPE_4__ {struct net_device* dev; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 unsigned int ETH_FRAME_LEN ; 
 unsigned int ETH_ZLEN ; 
 int /*<<< orphan*/  LDC_COPY_IN ; 
 unsigned int VNET_PACKET_SKIP ; 
 struct sk_buff* alloc_and_align_skb (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int ldc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct ldc_trans_cookie*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vnet_rx_one(struct vnet_port *port, unsigned int len,
		       struct ldc_trans_cookie *cookies, int ncookies)
{
	struct net_device *dev = port->vp->dev;
	unsigned int copy_len;
	struct sk_buff *skb;
	int err;

	err = -EMSGSIZE;
	if (unlikely(len < ETH_ZLEN || len > ETH_FRAME_LEN)) {
		dev->stats.rx_length_errors++;
		goto out_dropped;
	}

	skb = alloc_and_align_skb(dev, len);
	err = -ENOMEM;
	if (unlikely(!skb)) {
		dev->stats.rx_missed_errors++;
		goto out_dropped;
	}

	copy_len = (len + VNET_PACKET_SKIP + 7U) & ~7U;
	skb_put(skb, copy_len);
	err = ldc_copy(port->vio.lp, LDC_COPY_IN,
		       skb->data, copy_len, 0,
		       cookies, ncookies);
	if (unlikely(err < 0)) {
		dev->stats.rx_frame_errors++;
		goto out_free_skb;
	}

	skb_pull(skb, VNET_PACKET_SKIP);
	skb_trim(skb, len);
	skb->protocol = eth_type_trans(skb, dev);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	netif_rx(skb);

	return 0;

out_free_skb:
	kfree_skb(skb);

out_dropped:
	dev->stats.rx_dropped++;
	return err;
}