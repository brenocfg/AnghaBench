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
typedef  int /*<<< orphan*/  ulong ;
typedef  scalar_t__ u32 ;
struct pci_dn {TYPE_1__* phb; int /*<<< orphan*/  devfn; int /*<<< orphan*/  busno; } ;
struct TYPE_2__ {unsigned long buid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUID_HI (unsigned long) ; 
 int /*<<< orphan*/  BUID_LO (unsigned long) ; 
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  config_access_valid (struct pci_dn*,int) ; 
 int /*<<< orphan*/  ibm_write_pci_config ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ ,...) ; 
 unsigned long rtas_config_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_pci_config ; 

int rtas_write_config(struct pci_dn *pdn, int where, int size, u32 val)
{
	unsigned long buid, addr;
	int ret;

	if (!pdn)
		return PCIBIOS_DEVICE_NOT_FOUND;
	if (!config_access_valid(pdn, where))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	addr = rtas_config_addr(pdn->busno, pdn->devfn, where);
	buid = pdn->phb->buid;
	if (buid) {
		ret = rtas_call(ibm_write_pci_config, 5, 1, NULL, addr,
			BUID_HI(buid), BUID_LO(buid), size, (ulong) val);
	} else {
		ret = rtas_call(write_pci_config, 3, 1, NULL, addr, size, (ulong)val);
	}

	if (ret)
		return PCIBIOS_DEVICE_NOT_FOUND;

	return PCIBIOS_SUCCESSFUL;
}