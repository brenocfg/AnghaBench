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
struct TYPE_2__ {int idle; int phy_descs; int up; int /*<<< orphan*/  lock; scalar_t__ next_empty; int /*<<< orphan*/  descs; int /*<<< orphan*/  next_rx_desc; scalar_t__ next_rx; } ;
struct ns83820 {int IMR_cache; TYPE_1__ rx_info; int /*<<< orphan*/  misc_lock; scalar_t__ base; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCSR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IER ; 
 scalar_t__ IMR ; 
 int ISR_PHY ; 
 int ISR_RXDESC ; 
 int ISR_RXIDLE ; 
 int ISR_RXORN ; 
 int ISR_RXRCMP ; 
 int ISR_RXSOVR ; 
 int ISR_TXDESC ; 
 int ISR_TXIDLE ; 
 unsigned int NR_RX_DESC ; 
 struct ns83820* PRIV (struct net_device*) ; 
 scalar_t__ RFCR ; 
 scalar_t__ RXDP ; 
 scalar_t__ RXDP_HI ; 
 int /*<<< orphan*/  clear_rx_desc (struct ns83820*,unsigned int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  kick_rx (struct net_device*) ; 
 int /*<<< orphan*/  phy_intr (struct net_device*) ; 
 int rx_refill (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ns83820_setup_rx(struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);
	unsigned i;
	int ret;

	dprintk("ns83820_setup_rx(%p)\n", ndev);

	dev->rx_info.idle = 1;
	dev->rx_info.next_rx = 0;
	dev->rx_info.next_rx_desc = dev->rx_info.descs;
	dev->rx_info.next_empty = 0;

	for (i=0; i<NR_RX_DESC; i++)
		clear_rx_desc(dev, i);

	writel(0, dev->base + RXDP_HI);
	writel(dev->rx_info.phy_descs, dev->base + RXDP);

	ret = rx_refill(ndev, GFP_KERNEL);
	if (!ret) {
		dprintk("starting receiver\n");
		/* prevent the interrupt handler from stomping on us */
		spin_lock_irq(&dev->rx_info.lock);

		writel(0x0001, dev->base + CCSR);
		writel(0, dev->base + RFCR);
		writel(0x7fc00000, dev->base + RFCR);
		writel(0xffc00000, dev->base + RFCR);

		dev->rx_info.up = 1;

		phy_intr(ndev);

		/* Okay, let it rip */
		spin_lock_irq(&dev->misc_lock);
		dev->IMR_cache |= ISR_PHY;
		dev->IMR_cache |= ISR_RXRCMP;
		//dev->IMR_cache |= ISR_RXERR;
		//dev->IMR_cache |= ISR_RXOK;
		dev->IMR_cache |= ISR_RXORN;
		dev->IMR_cache |= ISR_RXSOVR;
		dev->IMR_cache |= ISR_RXDESC;
		dev->IMR_cache |= ISR_RXIDLE;
		dev->IMR_cache |= ISR_TXDESC;
		dev->IMR_cache |= ISR_TXIDLE;

		writel(dev->IMR_cache, dev->base + IMR);
		writel(1, dev->base + IER);
		spin_unlock(&dev->misc_lock);

		kick_rx(ndev);

		spin_unlock_irq(&dev->rx_info.lock);
	}
	return ret;
}