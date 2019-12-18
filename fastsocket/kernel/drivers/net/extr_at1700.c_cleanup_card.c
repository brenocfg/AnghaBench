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
struct net_local {scalar_t__ mca_slot; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT1700_IO_EXTENT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mca_mark_as_unused (scalar_t__) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_card(struct net_device *dev)
{
#ifdef CONFIG_MCA_LEGACY
	struct net_local *lp = netdev_priv(dev);
	if (lp->mca_slot >= 0)
		mca_mark_as_unused(lp->mca_slot);
#endif
	free_irq(dev->irq, NULL);
	release_region(dev->base_addr, AT1700_IO_EXTENT);
}