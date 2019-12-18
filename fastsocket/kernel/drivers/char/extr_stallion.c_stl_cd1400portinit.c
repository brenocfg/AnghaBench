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
struct stlport {int portnr; int uartaddr; int /*<<< orphan*/  brdnr; int /*<<< orphan*/  hwid; scalar_t__ pagenr; scalar_t__ ioaddr; } ;
struct stlpanel {scalar_t__ pagenr; scalar_t__ iobase; } ;
struct stlbrd {scalar_t__ brdtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ BRD_ECHPCI ; 
 int /*<<< orphan*/  CAR ; 
 scalar_t__ EREG_BANKSIZE ; 
 int /*<<< orphan*/  GFRCR ; 
 int /*<<< orphan*/  LIVR ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlbrd*,struct stlpanel*,struct stlport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stl_cd1400getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_cd1400setreg (struct stlport*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stl_cd1400portinit(struct stlbrd *brdp, struct stlpanel *panelp, struct stlport *portp)
{
	unsigned long flags;
	pr_debug("stl_cd1400portinit(brdp=%p,panelp=%p,portp=%p)\n", brdp,
			panelp, portp);

	if ((brdp == NULL) || (panelp == NULL) ||
	    (portp == NULL))
		return;

	spin_lock_irqsave(&brd_lock, flags);
	portp->ioaddr = panelp->iobase + (((brdp->brdtype == BRD_ECHPCI) ||
		(portp->portnr < 8)) ? 0 : EREG_BANKSIZE);
	portp->uartaddr = (portp->portnr & 0x04) << 5;
	portp->pagenr = panelp->pagenr + (portp->portnr >> 3);

	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_cd1400setreg(portp, CAR, (portp->portnr & 0x03));
	stl_cd1400setreg(portp, LIVR, (portp->portnr << 3));
	portp->hwid = stl_cd1400getreg(portp, GFRCR);
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
}