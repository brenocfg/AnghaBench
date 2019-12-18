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
struct virtnet_info {TYPE_2__* dev; int /*<<< orphan*/  svq; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_6__ {scalar_t__ num_sg; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sk_buff*) ; 
 TYPE_3__* skb_vnet_hdr (struct sk_buff*) ; 
 struct sk_buff* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int free_old_xmit_skbs(struct virtnet_info *vi)
{
	struct sk_buff *skb;
	unsigned int len, tot_sgs = 0;

	while ((skb = virtqueue_get_buf(vi->svq, &len)) != NULL) {
		pr_debug("Sent skb %p\n", skb);
		vi->dev->stats.tx_bytes += skb->len;
		vi->dev->stats.tx_packets++;
		tot_sgs += skb_vnet_hdr(skb)->num_sg;
		dev_kfree_skb_any(skb);
	}
	return tot_sgs;
}