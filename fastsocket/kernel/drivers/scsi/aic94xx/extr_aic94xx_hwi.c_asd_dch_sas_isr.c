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
 int CFIFTOERR ; 
 int /*<<< orphan*/  DCHSTATUS ; 
 int /*<<< orphan*/  asd_arp2_err (struct asd_ha_struct*,int) ; 
 int /*<<< orphan*/  asd_chip_reset (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_printk (char*,int /*<<< orphan*/ ) ; 
 int asd_read_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asd_dch_sas_isr(struct asd_ha_struct *asd_ha)
{
	u32 dchstatus = asd_read_reg_dword(asd_ha, DCHSTATUS);

	if (dchstatus & CFIFTOERR) {
		asd_printk("%s: CFIFTOERR\n", pci_name(asd_ha->pcidev));
		asd_chip_reset(asd_ha);
	} else
		asd_arp2_err(asd_ha, dchstatus);
}