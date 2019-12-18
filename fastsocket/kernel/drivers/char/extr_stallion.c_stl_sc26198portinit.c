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
struct stlport {int portnr; int uartaddr; int hwid; int /*<<< orphan*/  brdnr; int /*<<< orphan*/  pagenr; scalar_t__ ioaddr; } ;
struct stlpanel {int /*<<< orphan*/  pagenr; scalar_t__ iobase; } ;
struct stlbrd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOPCR ; 
 int /*<<< orphan*/  IOPCR_SETSIGS ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlbrd*,struct stlpanel*,struct stlport*) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stl_sc26198portinit(struct stlbrd *brdp, struct stlpanel *panelp, struct stlport *portp)
{
	pr_debug("stl_sc26198portinit(brdp=%p,panelp=%p,portp=%p)\n", brdp,
			panelp, portp);

	if ((brdp == NULL) || (panelp == NULL) ||
	    (portp == NULL))
		return;

	portp->ioaddr = panelp->iobase + ((portp->portnr < 8) ? 0 : 4);
	portp->uartaddr = (portp->portnr & 0x07) << 4;
	portp->pagenr = panelp->pagenr;
	portp->hwid = 0x1;

	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_sc26198setreg(portp, IOPCR, IOPCR_SETSIGS);
	BRDDISABLE(portp->brdnr);
}