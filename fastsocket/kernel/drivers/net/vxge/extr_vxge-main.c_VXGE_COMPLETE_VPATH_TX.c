#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vxge_fifo {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  handle; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int NR_SKB_COMPLETED ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 scalar_t__ spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vxge_hw_vpath_poll_tx (int /*<<< orphan*/ ,struct sk_buff***,int,int*) ; 

__attribute__((used)) static inline void VXGE_COMPLETE_VPATH_TX(struct vxge_fifo *fifo)
{
	unsigned long flags = 0;
	struct sk_buff **skb_ptr = NULL;
	struct sk_buff **temp;
#define NR_SKB_COMPLETED 128
	struct sk_buff *completed[NR_SKB_COMPLETED];
	int more;

	do {
		more = 0;
		skb_ptr = completed;

		if (spin_trylock_irqsave(&fifo->tx_lock, flags)) {
			vxge_hw_vpath_poll_tx(fifo->handle, &skb_ptr,
						NR_SKB_COMPLETED, &more);
			spin_unlock_irqrestore(&fifo->tx_lock, flags);
		}
		/* free SKBs */
		for (temp = completed; temp != skb_ptr; temp++)
			dev_kfree_skb_irq(*temp);
	} while (more) ;
}