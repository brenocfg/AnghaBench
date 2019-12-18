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
struct asd_ha_struct {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCIC_HSTPCIX_CNTRL ; 
 int SC_TMR_DIS ; 
 scalar_t__ asd_get_user_sas_addr (struct asd_ha_struct*) ; 
 int asd_init_chip (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_init_ctxmem (struct asd_ha_struct*) ; 
 int asd_init_dl (struct asd_ha_struct*) ; 
 int asd_init_escbs (struct asd_ha_struct*) ; 
 int asd_init_phys (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_init_ports (struct asd_ha_struct*) ; 
 int asd_init_scbs (struct asd_ha_struct*) ; 
 int asd_init_sw (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_printk (char*,...) ; 
 int /*<<< orphan*/  asd_propagate_sas_addr (struct asd_ha_struct*) ; 
 int asd_read_flash (struct asd_ha_struct*) ; 
 int asd_read_ocm (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int asd_init_hw(struct asd_ha_struct *asd_ha)
{
	int err;
	u32 v;

	err = asd_init_sw(asd_ha);
	if (err)
		return err;

	err = pci_read_config_dword(asd_ha->pcidev, PCIC_HSTPCIX_CNTRL, &v);
	if (err) {
		asd_printk("couldn't read PCIC_HSTPCIX_CNTRL of %s\n",
			   pci_name(asd_ha->pcidev));
		return err;
	}
	pci_write_config_dword(asd_ha->pcidev, PCIC_HSTPCIX_CNTRL,
					v | SC_TMR_DIS);
	if (err) {
		asd_printk("couldn't disable split completion timer of %s\n",
			   pci_name(asd_ha->pcidev));
		return err;
	}

	err = asd_read_ocm(asd_ha);
	if (err) {
		asd_printk("couldn't read ocm(%d)\n", err);
		/* While suspicios, it is not an error that we
		 * couldn't read the OCM. */
	}

	err = asd_read_flash(asd_ha);
	if (err) {
		asd_printk("couldn't read flash(%d)\n", err);
		/* While suspicios, it is not an error that we
		 * couldn't read FLASH memory.
		 */
	}

	asd_init_ctxmem(asd_ha);

	if (asd_get_user_sas_addr(asd_ha)) {
		asd_printk("No SAS Address provided for %s\n",
			   pci_name(asd_ha->pcidev));
		err = -ENODEV;
		goto Out;
	}

	asd_propagate_sas_addr(asd_ha);

	err = asd_init_phys(asd_ha);
	if (err) {
		asd_printk("couldn't initialize phys for %s\n",
			    pci_name(asd_ha->pcidev));
		goto Out;
	}

	asd_init_ports(asd_ha);

	err = asd_init_scbs(asd_ha);
	if (err) {
		asd_printk("couldn't initialize scbs for %s\n",
			    pci_name(asd_ha->pcidev));
		goto Out;
	}

	err = asd_init_dl(asd_ha);
	if (err) {
		asd_printk("couldn't initialize the done list:%d\n",
			    err);
		goto Out;
	}

	err = asd_init_escbs(asd_ha);
	if (err) {
		asd_printk("couldn't initialize escbs\n");
		goto Out;
	}

	err = asd_init_chip(asd_ha);
	if (err) {
		asd_printk("couldn't init the chip\n");
		goto Out;
	}
Out:
	return err;
}