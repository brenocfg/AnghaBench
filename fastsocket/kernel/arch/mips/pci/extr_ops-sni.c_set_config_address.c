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
typedef  unsigned int u32 ;

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 scalar_t__ PCIMT_CONFIG_ADDRESS ; 
 unsigned int PCI_DEVFN (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_config_address(unsigned int busno, unsigned int devfn, int reg)
{
	if ((devfn > 255) || (reg > 255))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	if (busno == 0 && devfn >= PCI_DEVFN(8, 0))
		return PCIBIOS_DEVICE_NOT_FOUND;

	*(volatile u32 *)PCIMT_CONFIG_ADDRESS =
		 ((busno    & 0xff) << 16) |
	         ((devfn    & 0xff) <<  8) |
	          (reg      & 0xfc);

	return PCIBIOS_SUCCESSFUL;
}