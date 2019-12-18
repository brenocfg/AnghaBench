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
struct net_device_stats {int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; } ;
struct net_device {int dummy; } ;
struct gem {struct net_device_stats net_stats; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_lock; scalar_t__ regs; scalar_t__ running; } ;

/* Variables and functions */
 scalar_t__ MAC_AERR ; 
 scalar_t__ MAC_ECOLL ; 
 scalar_t__ MAC_FCSERR ; 
 scalar_t__ MAC_LCOLL ; 
 scalar_t__ MAC_LERR ; 
 struct gem* netdev_priv (struct net_device*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct net_device_stats *gem_get_stats(struct net_device *dev)
{
	struct gem *gp = netdev_priv(dev);
	struct net_device_stats *stats = &gp->net_stats;

	spin_lock_irq(&gp->lock);
	spin_lock(&gp->tx_lock);

	/* I have seen this being called while the PM was in progress,
	 * so we shield against this
	 */
	if (gp->running) {
		stats->rx_crc_errors += readl(gp->regs + MAC_FCSERR);
		writel(0, gp->regs + MAC_FCSERR);

		stats->rx_frame_errors += readl(gp->regs + MAC_AERR);
		writel(0, gp->regs + MAC_AERR);

		stats->rx_length_errors += readl(gp->regs + MAC_LERR);
		writel(0, gp->regs + MAC_LERR);

		stats->tx_aborted_errors += readl(gp->regs + MAC_ECOLL);
		stats->collisions +=
			(readl(gp->regs + MAC_ECOLL) +
			 readl(gp->regs + MAC_LCOLL));
		writel(0, gp->regs + MAC_ECOLL);
		writel(0, gp->regs + MAC_LCOLL);
	}

	spin_unlock(&gp->tx_lock);
	spin_unlock_irq(&gp->lock);

	return &gp->net_stats;
}