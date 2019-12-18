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
struct stlpanel {int nrports; int iobase; int /*<<< orphan*/  brdnr; int /*<<< orphan*/  panelnr; scalar_t__ pagenr; } ;
struct stlbrd {scalar_t__ brdtype; int ioctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ BRD_ECHPCI ; 
 scalar_t__ CCR ; 
 int CCR_MAXWAIT ; 
 scalar_t__ CCR_RESETFULL ; 
 int CD1400_PORTS ; 
 int EREG_BANKSIZE ; 
 int EREG_DATA ; 
 scalar_t__ GFRCR ; 
 scalar_t__ PPR ; 
 scalar_t__ PPR_SCALAR ; 
 int /*<<< orphan*/  brd_lock ; 
 unsigned int inb (int) ; 
 int /*<<< orphan*/  outb (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlbrd*,struct stlpanel*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int stl_cd1400panelinit(struct stlbrd *brdp, struct stlpanel *panelp)
{
	unsigned int	gfrcr;
	int		chipmask, i, j;
	int		nrchips, uartaddr, ioaddr;
	unsigned long   flags;

	pr_debug("stl_panelinit(brdp=%p,panelp=%p)\n", brdp, panelp);

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(panelp->brdnr, panelp->pagenr);

/*
 *	Check that each chip is present and started up OK.
 */
	chipmask = 0;
	nrchips = panelp->nrports / CD1400_PORTS;
	for (i = 0; i < nrchips; i++) {
		if (brdp->brdtype == BRD_ECHPCI) {
			outb((panelp->pagenr + (i >> 1)), brdp->ioctrl);
			ioaddr = panelp->iobase;
		} else
			ioaddr = panelp->iobase + (EREG_BANKSIZE * (i >> 1));
		uartaddr = (i & 0x01) ? 0x080 : 0;
		outb((GFRCR + uartaddr), ioaddr);
		outb(0, (ioaddr + EREG_DATA));
		outb((CCR + uartaddr), ioaddr);
		outb(CCR_RESETFULL, (ioaddr + EREG_DATA));
		outb(CCR_RESETFULL, (ioaddr + EREG_DATA));
		outb((GFRCR + uartaddr), ioaddr);
		for (j = 0; j < CCR_MAXWAIT; j++)
			if ((gfrcr = inb(ioaddr + EREG_DATA)) != 0)
				break;

		if ((j >= CCR_MAXWAIT) || (gfrcr < 0x40) || (gfrcr > 0x60)) {
			printk("STALLION: cd1400 not responding, "
				"brd=%d panel=%d chip=%d\n",
				panelp->brdnr, panelp->panelnr, i);
			continue;
		}
		chipmask |= (0x1 << i);
		outb((PPR + uartaddr), ioaddr);
		outb(PPR_SCALAR, (ioaddr + EREG_DATA));
	}

	BRDDISABLE(panelp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
	return chipmask;
}