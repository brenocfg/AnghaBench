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
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; } ;
struct mc32_local {unsigned int slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC32_IO_EXTENT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mca_mark_as_unused (unsigned int) ; 
 int /*<<< orphan*/  mca_set_adapter_name (unsigned int,int /*<<< orphan*/ *) ; 
 struct mc32_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_card(struct net_device *dev)
{
	struct mc32_local *lp = netdev_priv(dev);
	unsigned slot = lp->slot;
	mca_mark_as_unused(slot);
	mca_set_adapter_name(slot, NULL);
	free_irq(dev->irq, dev);
	release_region(dev->base_addr, MC32_IO_EXTENT);
}