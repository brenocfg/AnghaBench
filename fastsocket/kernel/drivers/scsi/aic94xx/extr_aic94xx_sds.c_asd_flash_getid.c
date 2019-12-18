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
typedef  int u32 ;
struct TYPE_3__ {int present; int wide; int /*<<< orphan*/  bar; } ;
struct TYPE_4__ {TYPE_1__ flash; } ;
struct asd_ha_struct {TYPE_2__ hw_prof; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  EXSICNFGR ; 
 int FLASHW ; 
 int /*<<< orphan*/  PCI_CONF_FLSH_BAR ; 
 int /*<<< orphan*/  asd_printk (char*,int /*<<< orphan*/ ) ; 
 int asd_read_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int asd_reset_flash (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asd_flash_getid(struct asd_ha_struct *asd_ha)
{
	int err = 0;
	u32 reg;

	reg = asd_read_reg_dword(asd_ha, EXSICNFGR);

	if (pci_read_config_dword(asd_ha->pcidev, PCI_CONF_FLSH_BAR,
				  &asd_ha->hw_prof.flash.bar)) {
		asd_printk("couldn't read PCI_CONF_FLSH_BAR of %s\n",
			   pci_name(asd_ha->pcidev));
		return -ENOENT;
	}
	asd_ha->hw_prof.flash.present = 1;
	asd_ha->hw_prof.flash.wide = reg & FLASHW ? 1 : 0;
	err = asd_reset_flash(asd_ha);
	if (err) {
		ASD_DPRINTK("couldn't reset flash(%d)\n", err);
		return err;
	}
	return 0;
}