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
struct TYPE_3__ {scalar_t__ pci_cfg; scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ diva; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ DIVA_IPACX_PCI ; 
 scalar_t__ DIVA_IPAC_PCI ; 
 int /*<<< orphan*/  iounmap (void*) ; 

__attribute__((used)) static void
iounmap_diva(struct IsdnCardState *cs)
{
	if ((cs->subtyp == DIVA_IPAC_PCI) || (cs->subtyp == DIVA_IPACX_PCI)) {
		if (cs->hw.diva.cfg_reg) {
			iounmap((void *)cs->hw.diva.cfg_reg);
			cs->hw.diva.cfg_reg = 0;
		}
		if (cs->hw.diva.pci_cfg) {
			iounmap((void *)cs->hw.diva.pci_cfg);
			cs->hw.diva.pci_cfg = 0;
		}
	}

	return;
}