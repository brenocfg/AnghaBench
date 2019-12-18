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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  au1000_rx (struct net_device*) ; 
 int /*<<< orphan*/  au1000_tx_ack (struct net_device*) ; 

__attribute__((used)) static irqreturn_t au1000_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;

	/* Handle RX interrupts first to minimize chance of overrun */

	au1000_rx(dev);
	au1000_tx_ack(dev);
	return IRQ_RETVAL(1);
}