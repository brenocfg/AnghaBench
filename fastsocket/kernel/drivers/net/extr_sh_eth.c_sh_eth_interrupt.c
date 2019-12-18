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
typedef  int u32 ;
struct sh_eth_private {int /*<<< orphan*/  lock; struct sh_eth_cpu_data* cd; } ;
struct sh_eth_cpu_data {int tx_check; int eesr_err_check; } ;
struct net_device {int base_addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EESR ; 
 int EESR_CERF ; 
 int EESR_FRC ; 
 int EESR_PRE ; 
 int EESR_RMAF ; 
 int EESR_RRF ; 
 int EESR_RTLF ; 
 int EESR_RTSF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ctrl_inl (int) ; 
 int /*<<< orphan*/  ctrl_outl (int,int) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_error (struct net_device*,int) ; 
 int /*<<< orphan*/  sh_eth_rx (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_txfree (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sh_eth_interrupt(int irq, void *netdev)
{
	struct net_device *ndev = netdev;
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct sh_eth_cpu_data *cd = mdp->cd;
	irqreturn_t ret = IRQ_NONE;
	u32 ioaddr, intr_status = 0;

	ioaddr = ndev->base_addr;
	spin_lock(&mdp->lock);

	/* Get interrpt stat */
	intr_status = ctrl_inl(ioaddr + EESR);
	/* Clear interrupt */
	if (intr_status & (EESR_FRC | EESR_RMAF | EESR_RRF |
			EESR_RTLF | EESR_RTSF | EESR_PRE | EESR_CERF |
			cd->tx_check | cd->eesr_err_check)) {
		ctrl_outl(intr_status, ioaddr + EESR);
		ret = IRQ_HANDLED;
	} else
		goto other_irq;

	if (intr_status & (EESR_FRC | /* Frame recv*/
			EESR_RMAF | /* Multi cast address recv*/
			EESR_RRF  | /* Bit frame recv */
			EESR_RTLF | /* Long frame recv*/
			EESR_RTSF | /* short frame recv */
			EESR_PRE  | /* PHY-LSI recv error */
			EESR_CERF)){ /* recv frame CRC error */
		sh_eth_rx(ndev);
	}

	/* Tx Check */
	if (intr_status & cd->tx_check) {
		sh_eth_txfree(ndev);
		netif_wake_queue(ndev);
	}

	if (intr_status & cd->eesr_err_check)
		sh_eth_error(ndev, intr_status);

other_irq:
	spin_unlock(&mdp->lock);

	return ret;
}