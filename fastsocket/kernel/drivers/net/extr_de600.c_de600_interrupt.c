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
typedef  int u8 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RX_BUSY ; 
 int /*<<< orphan*/  RX_ENABLE ; 
 int RX_GOOD ; 
 scalar_t__ TX_PAGES ; 
 int /*<<< orphan*/  de600_lock ; 
 int /*<<< orphan*/  de600_put_command (int /*<<< orphan*/ ) ; 
 int de600_read_status (struct net_device*) ; 
 int /*<<< orphan*/  de600_rx_intr (struct net_device*) ; 
 int de600_tx_intr (struct net_device*,int) ; 
 scalar_t__ free_tx_pages ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  select_nic () ; 
 int /*<<< orphan*/  select_prn () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trigger_interrupt (struct net_device*) ; 

__attribute__((used)) static irqreturn_t de600_interrupt(int irq, void *dev_id)
{
	struct net_device	*dev = dev_id;
	u8		irq_status;
	int		retrig = 0;
	int		boguscount = 0;

	spin_lock(&de600_lock);

	select_nic();
	irq_status = de600_read_status(dev);

	do {
		pr_debug("de600_interrupt (%02X)\n", irq_status);

		if (irq_status & RX_GOOD)
			de600_rx_intr(dev);
		else if (!(irq_status & RX_BUSY))
			de600_put_command(RX_ENABLE);

		/* Any transmission in progress? */
		if (free_tx_pages < TX_PAGES)
			retrig = de600_tx_intr(dev, irq_status);
		else
			retrig = 0;

		irq_status = de600_read_status(dev);
	} while ( (irq_status & RX_GOOD) || ((++boguscount < 100) && retrig) );
	/*
	 * Yeah, it _looks_ like busy waiting, smells like busy waiting
	 * and I know it's not PC, but please, it will only occur once
	 * in a while and then only for a loop or so (< 1ms for sure!)
	 */

	/* Enable adapter interrupts */
	select_prn();
	if (retrig)
		trigger_interrupt(dev);
	spin_unlock(&de600_lock);
	return IRQ_HANDLED;
}