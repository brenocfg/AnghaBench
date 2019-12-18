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
typedef  int /*<<< orphan*/  u16 ;
struct pci_controller {int dummy; } ;

/* Variables and functions */
 int scc_pciex_read_port (struct pci_controller*,unsigned long,int) ; 

__attribute__((used)) static u16 __scc_pciex_inw(struct pci_controller *phb, unsigned long port)
{
	u32 data;
	if ((port & 0x3ul) < 3)
		data = scc_pciex_read_port(phb, port, 2);
	else {
		u32 d1 = scc_pciex_read_port(phb, port, 1);
		u32 d2 = scc_pciex_read_port(phb, port + 1, 1);
		data = d1 | (d2 << 8);
	}
	return (u16)data;
}