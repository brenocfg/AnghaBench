#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {scalar_t__ cfg_reg; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  tl; scalar_t__ pci_cfg; } ;
struct TYPE_4__ {TYPE_1__ diva; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ DIVA_IPACX_PCI ; 
 scalar_t__ DIVA_IPAC_ISA ; 
 scalar_t__ DIVA_IPAC_PCI ; 
 scalar_t__ DIVA_ISA ; 
 int /*<<< orphan*/  byteout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void
release_io_diva(struct IsdnCardState *cs)
{
	int bytecnt;

	if ((cs->subtyp == DIVA_IPAC_PCI) || 
	    (cs->subtyp == DIVA_IPACX_PCI)   ) {
		u_int *cfg = (unsigned int *)cs->hw.diva.pci_cfg;

		*cfg = 0; /* disable INT0/1 */ 
		*cfg = 2; /* reset pending INT0 */
		if (cs->hw.diva.cfg_reg)
			iounmap((void *)cs->hw.diva.cfg_reg);
		if (cs->hw.diva.pci_cfg)
			iounmap((void *)cs->hw.diva.pci_cfg);
		return;
	} else if (cs->subtyp != DIVA_IPAC_ISA) {
		del_timer(&cs->hw.diva.tl);
		if (cs->hw.diva.cfg_reg)
			byteout(cs->hw.diva.ctrl, 0); /* LED off, Reset */
	}
	if ((cs->subtyp == DIVA_ISA) || (cs->subtyp == DIVA_IPAC_ISA))
		bytecnt = 8;
	else
		bytecnt = 32;
	if (cs->hw.diva.cfg_reg) {
		release_region(cs->hw.diva.cfg_reg, bytecnt);
	}
}