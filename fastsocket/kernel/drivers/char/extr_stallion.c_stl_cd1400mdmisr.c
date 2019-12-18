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
struct TYPE_2__ {int /*<<< orphan*/  modem; } ;
struct stlport {scalar_t__ uartaddr; TYPE_1__ stats; } ;
struct stlpanel {unsigned int ackmask; struct stlport** ports; } ;

/* Variables and functions */
 unsigned int ACK_TYPMASK ; 
 unsigned int ACK_TYPMDM ; 
 scalar_t__ EOSRR ; 
 int EREG_DATA ; 
 int EREG_MDACK ; 
 scalar_t__ MISR ; 
 unsigned char MISR_DCD ; 
 void* inb (int) ; 
 int /*<<< orphan*/  outb (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlpanel*) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 int /*<<< orphan*/  stl_cd_change (struct stlport*) ; 

__attribute__((used)) static void stl_cd1400mdmisr(struct stlpanel *panelp, int ioaddr)
{
	struct stlport	*portp;
	unsigned int	ioack;
	unsigned char	misr;

	pr_debug("stl_cd1400mdmisr(panelp=%p)\n", panelp);

	ioack = inb(ioaddr + EREG_MDACK);
	if (((ioack & panelp->ackmask) != 0) ||
	    ((ioack & ACK_TYPMASK) != ACK_TYPMDM)) {
		printk("STALLION: bad MODEM interrupt ack value=%x\n", ioack);
		return;
	}
	portp = panelp->ports[(ioack >> 3)];

	outb((MISR + portp->uartaddr), ioaddr);
	misr = inb(ioaddr + EREG_DATA);
	if (misr & MISR_DCD) {
		stl_cd_change(portp);
		portp->stats.modem++;
	}

	outb((EOSRR + portp->uartaddr), ioaddr);
	outb(0, (ioaddr + EREG_DATA));
}