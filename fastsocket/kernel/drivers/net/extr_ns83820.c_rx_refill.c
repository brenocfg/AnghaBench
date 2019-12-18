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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct ns83820 {TYPE_1__ rx_info; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ GFP_ATOMIC ; 
 unsigned int NR_RX_DESC ; 
 struct ns83820* PRIV (struct net_device*) ; 
 scalar_t__ PTR_ALIGN (scalar_t__,int) ; 
 scalar_t__ REAL_RX_BUF_SIZE ; 
 struct sk_buff* __netdev_alloc_skb (struct net_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,struct net_device*) ; 
 int nr_rx_empty (struct ns83820*) ; 
 long ns83820_add_rx_skb (struct ns83820*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int rx_refill(struct net_device *ndev, gfp_t gfp)
{
	struct ns83820 *dev = PRIV(ndev);
	unsigned i;
	unsigned long flags = 0;

	if (unlikely(nr_rx_empty(dev) <= 2))
		return 0;

	dprintk("rx_refill(%p)\n", ndev);
	if (gfp == GFP_ATOMIC)
		spin_lock_irqsave(&dev->rx_info.lock, flags);
	for (i=0; i<NR_RX_DESC; i++) {
		struct sk_buff *skb;
		long res;

		/* extra 16 bytes for alignment */
		skb = __netdev_alloc_skb(ndev, REAL_RX_BUF_SIZE+16, gfp);
		if (unlikely(!skb))
			break;

		skb_reserve(skb, skb->data - PTR_ALIGN(skb->data, 16));
		if (gfp != GFP_ATOMIC)
			spin_lock_irqsave(&dev->rx_info.lock, flags);
		res = ns83820_add_rx_skb(dev, skb);
		if (gfp != GFP_ATOMIC)
			spin_unlock_irqrestore(&dev->rx_info.lock, flags);
		if (res) {
			i = 1;
			break;
		}
	}
	if (gfp == GFP_ATOMIC)
		spin_unlock_irqrestore(&dev->rx_info.lock, flags);

	return i ? 0 : -ENOMEM;
}