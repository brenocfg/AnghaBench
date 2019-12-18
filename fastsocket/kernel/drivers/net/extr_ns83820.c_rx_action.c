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
struct ns83820 {int /*<<< orphan*/  misc_lock; scalar_t__ base; int /*<<< orphan*/  IMR_cache; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IHR ; 
 scalar_t__ IMR ; 
 int /*<<< orphan*/  ISR_RXDESC ; 
 struct ns83820* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  ihr ; 
 int /*<<< orphan*/  ns83820_rx_kick (struct net_device*) ; 
 int /*<<< orphan*/  rx_irq (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rx_action(unsigned long _dev)
{
	struct net_device *ndev = (void *)_dev;
	struct ns83820 *dev = PRIV(ndev);
	rx_irq(ndev);
	writel(ihr, dev->base + IHR);

	spin_lock_irq(&dev->misc_lock);
	dev->IMR_cache |= ISR_RXDESC;
	writel(dev->IMR_cache, dev->base + IMR);
	spin_unlock_irq(&dev->misc_lock);

	rx_irq(ndev);
	ns83820_rx_kick(ndev);
}