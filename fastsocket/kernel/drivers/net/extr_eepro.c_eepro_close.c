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
struct net_device {int base_addr; int /*<<< orphan*/  irq; } ;
struct eepro_local {scalar_t__ tx_last; int /*<<< orphan*/  xmt_lower_limit; int /*<<< orphan*/  tx_end; int /*<<< orphan*/  tx_start; } ;

/* Variables and functions */
 int REG1 ; 
 short STOP_RCV_CMD ; 
 int /*<<< orphan*/  eepro_clear_int (int) ; 
 int /*<<< orphan*/  eepro_dis_int (int) ; 
 int /*<<< orphan*/  eepro_reset (int) ; 
 int /*<<< orphan*/  eepro_sw2bank0 (int) ; 
 int /*<<< orphan*/  eepro_sw2bank1 (int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 short inb (int) ; 
 struct eepro_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (short,int) ; 

__attribute__((used)) static int eepro_close(struct net_device *dev)
{
	struct eepro_local *lp = netdev_priv(dev);
	int ioaddr = dev->base_addr;
	short temp_reg;

	netif_stop_queue(dev);

	eepro_sw2bank1(ioaddr); /* Switch back to Bank 1 */

	/* Disable the physical interrupt line. */
	temp_reg = inb(ioaddr + REG1);
	outb(temp_reg & 0x7f, ioaddr + REG1);

	eepro_sw2bank0(ioaddr); /* Switch back to Bank 0 */

	/* Flush the Tx and disable Rx. */
	outb(STOP_RCV_CMD, ioaddr);
	lp->tx_start = lp->tx_end = lp->xmt_lower_limit;
	lp->tx_last = 0;

	/* Mask all the interrupts. */
	eepro_dis_int(ioaddr);

	/* clear all interrupts */
	eepro_clear_int(ioaddr);

	/* Reset the 82595 */
	eepro_reset(ioaddr);

	/* release the interrupt */
	free_irq(dev->irq, dev);

	/* Update the statistics here. What statistics? */

	return 0;
}