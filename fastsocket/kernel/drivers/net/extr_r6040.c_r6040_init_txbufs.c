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
struct r6040_private {int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  tx_insert_ptr; int /*<<< orphan*/  tx_remove_ptr; int /*<<< orphan*/  tx_free_desc; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_DCNT ; 
 struct r6040_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  r6040_init_ring_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r6040_init_txbufs(struct net_device *dev)
{
	struct r6040_private *lp = netdev_priv(dev);

	lp->tx_free_desc = TX_DCNT;

	lp->tx_remove_ptr = lp->tx_insert_ptr = lp->tx_ring;
	r6040_init_ring_desc(lp->tx_ring, lp->tx_ring_dma, TX_DCNT);
}