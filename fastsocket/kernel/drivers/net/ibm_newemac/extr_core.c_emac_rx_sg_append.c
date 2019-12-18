#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rx_dropped_mtu; } ;
struct emac_instance {int rx_skb_size; TYPE_4__* rx_sg_skb; TYPE_3__** rx_skb; TYPE_2__ estats; TYPE_1__* rx_desc; } ;
struct TYPE_10__ {int len; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int data_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  cacheable_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_4__*) ; 
 int /*<<< orphan*/  emac_recycle_rx_skb (struct emac_instance*,int,int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (TYPE_4__*,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int emac_rx_sg_append(struct emac_instance *dev, int slot)
{
	if (likely(dev->rx_sg_skb != NULL)) {
		int len = dev->rx_desc[slot].data_len;
		int tot_len = dev->rx_sg_skb->len + len;

		if (unlikely(tot_len + 2 > dev->rx_skb_size)) {
			++dev->estats.rx_dropped_mtu;
			dev_kfree_skb(dev->rx_sg_skb);
			dev->rx_sg_skb = NULL;
		} else {
			cacheable_memcpy(skb_tail_pointer(dev->rx_sg_skb),
					 dev->rx_skb[slot]->data, len);
			skb_put(dev->rx_sg_skb, len);
			emac_recycle_rx_skb(dev, slot, len);
			return 0;
		}
	}
	emac_recycle_rx_skb(dev, slot, 0);
	return -1;
}