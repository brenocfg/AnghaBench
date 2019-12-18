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
struct ioc3_private {int emcr; int /*<<< orphan*/  ehar_l; int /*<<< orphan*/  ehar_h; int /*<<< orphan*/  ioc3_timer; struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int EISR_RXBUFOFLO ; 
 int EISR_RXMEMERR ; 
 int EISR_RXOFLO ; 
 int EISR_RXPARERR ; 
 int EISR_RXTIMERINT ; 
 int EISR_TXBUFUFLO ; 
 int EISR_TXEXPLICIT ; 
 int EISR_TXMEMERR ; 
 int EMCR_PADEN ; 
 int EMCR_RST ; 
 int EMCR_RXDMAEN ; 
 int EMCR_RXEN ; 
 int EMCR_RXOFF_SHIFT ; 
 int EMCR_TXDMAEN ; 
 int EMCR_TXEN ; 
 int PCI64_ATTR_BAR ; 
 int RX_OFFSET ; 
 int /*<<< orphan*/  __ioc3_set_mac_address (struct net_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioc3_init_rings (struct net_device*) ; 
 int /*<<< orphan*/  ioc3_r_eier () ; 
 int /*<<< orphan*/  ioc3_r_emcr () ; 
 int /*<<< orphan*/  ioc3_r_etcdc () ; 
 int /*<<< orphan*/  ioc3_w_ehar_h (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc3_w_ehar_l (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc3_w_eier (int) ; 
 int /*<<< orphan*/  ioc3_w_emcr (int) ; 
 int /*<<< orphan*/  ioc3_w_erbar (int) ; 
 int /*<<< orphan*/  ioc3_w_ercsr (int) ; 
 int /*<<< orphan*/  ioc3_w_ersr (int) ; 
 int /*<<< orphan*/  ioc3_w_ertr (int /*<<< orphan*/ ) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ioc3_init(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3 *ioc3 = ip->regs;

	del_timer_sync(&ip->ioc3_timer);	/* Kill if running	*/

	ioc3_w_emcr(EMCR_RST);			/* Reset		*/
	(void) ioc3_r_emcr();			/* Flush WB		*/
	udelay(4);				/* Give it time ...	*/
	ioc3_w_emcr(0);
	(void) ioc3_r_emcr();

	/* Misc registers  */
#ifdef CONFIG_SGI_IP27
	ioc3_w_erbar(PCI64_ATTR_BAR >> 32);	/* Barrier on last store */
#else
	ioc3_w_erbar(0);			/* Let PCI API get it right */
#endif
	(void) ioc3_r_etcdc();			/* Clear on read */
	ioc3_w_ercsr(15);			/* RX low watermark  */
	ioc3_w_ertr(0);				/* Interrupt immediately */
	__ioc3_set_mac_address(dev);
	ioc3_w_ehar_h(ip->ehar_h);
	ioc3_w_ehar_l(ip->ehar_l);
	ioc3_w_ersr(42);			/* XXX should be random */

	ioc3_init_rings(dev);

	ip->emcr |= ((RX_OFFSET / 2) << EMCR_RXOFF_SHIFT) | EMCR_TXDMAEN |
	             EMCR_TXEN | EMCR_RXDMAEN | EMCR_RXEN | EMCR_PADEN;
	ioc3_w_emcr(ip->emcr);
	ioc3_w_eier(EISR_RXTIMERINT | EISR_RXOFLO | EISR_RXBUFOFLO |
	            EISR_RXMEMERR | EISR_RXPARERR | EISR_TXBUFUFLO |
	            EISR_TXEXPLICIT | EISR_TXMEMERR);
	(void) ioc3_r_eier();
}