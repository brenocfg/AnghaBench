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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {struct sk_buff** skbs; scalar_t__ up; } ;
struct ns83820 {int IMR_cache; TYPE_2__ rx_info; scalar_t__ base; TYPE_1__* pci_dev; int /*<<< orphan*/  misc_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ IMR ; 
 int ISR_RXDESC ; 
 int ISR_RXEARLY ; 
 int ISR_RXERR ; 
 int ISR_RXIDLE ; 
 int ISR_RXOK ; 
 unsigned int NR_RX_DESC ; 
 scalar_t__ RXDP ; 
 scalar_t__ RXDP_HI ; 
 int /*<<< orphan*/  clear_rx_desc (struct ns83820*,unsigned int) ; 
 int /*<<< orphan*/  dprintk (char*,struct ns83820*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ns83820_cleanup_rx(struct ns83820 *dev)
{
	unsigned i;
	unsigned long flags;

	dprintk("ns83820_cleanup_rx(%p)\n", dev);

	/* disable receive interrupts */
	spin_lock_irqsave(&dev->misc_lock, flags);
	dev->IMR_cache &= ~(ISR_RXOK | ISR_RXDESC | ISR_RXERR | ISR_RXEARLY | ISR_RXIDLE);
	writel(dev->IMR_cache, dev->base + IMR);
	spin_unlock_irqrestore(&dev->misc_lock, flags);

	/* synchronize with the interrupt handler and kill it */
	dev->rx_info.up = 0;
	synchronize_irq(dev->pci_dev->irq);

	/* touch the pci bus... */
	readl(dev->base + IMR);

	/* assumes the transmitter is already disabled and reset */
	writel(0, dev->base + RXDP_HI);
	writel(0, dev->base + RXDP);

	for (i=0; i<NR_RX_DESC; i++) {
		struct sk_buff *skb = dev->rx_info.skbs[i];
		dev->rx_info.skbs[i] = NULL;
		clear_rx_desc(dev, i);
		kfree_skb(skb);
	}
}