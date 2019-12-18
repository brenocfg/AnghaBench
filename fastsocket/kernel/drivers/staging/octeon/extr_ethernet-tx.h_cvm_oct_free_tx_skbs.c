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
struct octeon_ethernet {TYPE_1__* tx_free_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cvm_oct_free_tx_skbs(struct octeon_ethernet *priv,
					int skb_to_free,
					int qos, int take_lock)
{
	/* Free skbuffs not in use by the hardware.  */
	if (skb_to_free > 0) {
		if (take_lock)
			spin_lock(&priv->tx_free_list[qos].lock);
		while (skb_to_free > 0) {
			dev_kfree_skb(__skb_dequeue(&priv->tx_free_list[qos]));
			skb_to_free--;
		}
		if (take_lock)
			spin_unlock(&priv->tx_free_list[qos].lock);
	}
}