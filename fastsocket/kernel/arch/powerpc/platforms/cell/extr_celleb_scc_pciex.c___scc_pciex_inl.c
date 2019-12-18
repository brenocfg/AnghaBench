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
struct pci_controller {int dummy; } ;

/* Variables and functions */
 unsigned int scc_pciex_read_port (struct pci_controller*,unsigned long,unsigned int) ; 

__attribute__((used)) static u32 __scc_pciex_inl(struct pci_controller *phb, unsigned long port)
{
	unsigned int mod = port & 0x3ul;
	u32 data;
	if (mod == 0)
		data = scc_pciex_read_port(phb, port, 4);
	else {
		u32 d1 = scc_pciex_read_port(phb, port, 4 - mod);
		u32 d2 = scc_pciex_read_port(phb, port + 1, mod);
		data = d1 | (d2 << (mod * 8));
	}
	return data;
}