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
struct net_device {int dummy; } ;
struct ioc3_private {struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EISR_RXBUFOFLO ; 
 int EISR_RXMEMERR ; 
 int EISR_RXOFLO ; 
 int EISR_RXPARERR ; 
 int EISR_RXTIMERINT ; 
 int EISR_TXBUFUFLO ; 
 int EISR_TXEXPLICIT ; 
 int EISR_TXMEMERR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ioc3_error (struct ioc3_private*,int) ; 
 int const ioc3_r_eisr () ; 
 int /*<<< orphan*/  ioc3_rx (struct ioc3_private*) ; 
 int /*<<< orphan*/  ioc3_tx (struct ioc3_private*) ; 
 int /*<<< orphan*/  ioc3_w_eisr (int) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t ioc3_interrupt(int irq, void *_dev)
{
	struct net_device *dev = (struct net_device *)_dev;
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3 *ioc3 = ip->regs;
	const u32 enabled = EISR_RXTIMERINT | EISR_RXOFLO | EISR_RXBUFOFLO |
	                    EISR_RXMEMERR | EISR_RXPARERR | EISR_TXBUFUFLO |
	                    EISR_TXEXPLICIT | EISR_TXMEMERR;
	u32 eisr;

	eisr = ioc3_r_eisr() & enabled;

	ioc3_w_eisr(eisr);
	(void) ioc3_r_eisr();				/* Flush */

	if (eisr & (EISR_RXOFLO | EISR_RXBUFOFLO | EISR_RXMEMERR |
	            EISR_RXPARERR | EISR_TXBUFUFLO | EISR_TXMEMERR))
		ioc3_error(ip, eisr);
	if (eisr & EISR_RXTIMERINT)
		ioc3_rx(ip);
	if (eisr & EISR_TXEXPLICIT)
		ioc3_tx(ip);

	return IRQ_HANDLED;
}