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
struct stlpanel {int /*<<< orphan*/  (* isr ) (struct stlpanel*,unsigned int) ;} ;
struct stlbrd {unsigned int iostatus; unsigned int nrbnks; unsigned int* bnkstataddr; struct stlpanel** bnk2panel; } ;

/* Variables and functions */
 int ECH_INTRPEND ; 
 int ECH_PNLINTRPEND ; 
 int inb (unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct stlpanel*,unsigned int) ; 

__attribute__((used)) static int stl_echmcaintr(struct stlbrd *brdp)
{
	struct stlpanel	*panelp;
	unsigned int	ioaddr, bnknr;
	int		handled = 0;

	while (inb(brdp->iostatus) & ECH_INTRPEND) {
		handled = 1;
		for (bnknr = 0; bnknr < brdp->nrbnks; bnknr++) {
			ioaddr = brdp->bnkstataddr[bnknr];
			if (inb(ioaddr) & ECH_PNLINTRPEND) {
				panelp = brdp->bnk2panel[bnknr];
				(* panelp->isr)(panelp, (ioaddr & 0xfffc));
			}
		}
	}
	return handled;
}