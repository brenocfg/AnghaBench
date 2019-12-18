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
typedef  int u16 ;
struct net_device {scalar_t__ base_addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ BCMREG ; 
 int BCMREG_IPEND ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ISREG_PKTRX ; 
 int ISREG_RBE ; 
 int ISREG_TXDN ; 
 int ISREG_TXER ; 
 scalar_t__ SONIC_ISREG ; 
 int inb (scalar_t__) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  irqrbe_handler (struct net_device*) ; 
 int /*<<< orphan*/  irqrx_handler (struct net_device*) ; 
 int /*<<< orphan*/  irqtx_handler (struct net_device*) ; 
 int /*<<< orphan*/  irqtxerr_handler (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t irq_handler(int dummy, void *device)
{
	struct net_device *dev = device;
	u16 ival;

	/* in case we're not meant... */
	if (!(inb(dev->base_addr + BCMREG) & BCMREG_IPEND))
		return IRQ_NONE;

	/* loop through the interrupt bits until everything is clear */
	while (1) {
		ival = inw(dev->base_addr + SONIC_ISREG);

		if (ival & ISREG_RBE) {
			irqrbe_handler(dev);
			outw(ISREG_RBE, dev->base_addr + SONIC_ISREG);
		}
		if (ival & ISREG_PKTRX) {
			irqrx_handler(dev);
			outw(ISREG_PKTRX, dev->base_addr + SONIC_ISREG);
		}
		if (ival & ISREG_TXDN) {
			irqtx_handler(dev);
			outw(ISREG_TXDN, dev->base_addr + SONIC_ISREG);
		}
		if (ival & ISREG_TXER) {
			irqtxerr_handler(dev);
			outw(ISREG_TXER, dev->base_addr + SONIC_ISREG);
		}
		break;
	}
	return IRQ_HANDLED;
}