#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ up; } ;
struct ns83820 {int IMR_cache; int /*<<< orphan*/  misc_lock; TYPE_2__* pci_dev; TYPE_1__ rx_info; scalar_t__ base; int /*<<< orphan*/  tx_watchdog; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_RST ; 
 scalar_t__ IER ; 
 scalar_t__ IMR ; 
 int ISR_TXDESC ; 
 int ISR_TXERR ; 
 int ISR_TXIDLE ; 
 int ISR_TXOK ; 
 int ISR_TXURN ; 
 struct ns83820* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns83820_cleanup_rx (struct ns83820*) ; 
 int /*<<< orphan*/  ns83820_cleanup_tx (struct ns83820*) ; 
 int /*<<< orphan*/  ns83820_do_reset (struct ns83820*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ns83820_stop(struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);

	/* FIXME: protect against interrupt handler? */
	del_timer_sync(&dev->tx_watchdog);

	/* disable interrupts */
	writel(0, dev->base + IMR);
	writel(0, dev->base + IER);
	readl(dev->base + IER);

	dev->rx_info.up = 0;
	synchronize_irq(dev->pci_dev->irq);

	ns83820_do_reset(dev, CR_RST);

	synchronize_irq(dev->pci_dev->irq);

	spin_lock_irq(&dev->misc_lock);
	dev->IMR_cache &= ~(ISR_TXURN | ISR_TXIDLE | ISR_TXERR | ISR_TXDESC | ISR_TXOK);
	spin_unlock_irq(&dev->misc_lock);

	ns83820_cleanup_rx(dev);
	ns83820_cleanup_tx(dev);

	return 0;
}