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

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  outl (int,int) ; 

__attribute__((used)) static int pcit_set_config_address(unsigned int busno, unsigned int devfn, int reg)
{
	if ((devfn > 255) || (reg > 255) || (busno > 255))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	outl((1 << 31) | ((busno & 0xff) << 16) | ((devfn & 0xff) << 8) | (reg & 0xfc), 0xcf8);
	return PCIBIOS_SUCCESSFUL;
}