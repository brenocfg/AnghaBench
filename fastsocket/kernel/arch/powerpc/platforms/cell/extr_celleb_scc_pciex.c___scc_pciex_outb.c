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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scc_pciex_write_port (struct pci_controller*,unsigned long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __scc_pciex_outb(struct pci_controller *phb,
			     u8 val, unsigned long port)
{
	scc_pciex_write_port(phb, port, 1, (u32)val);
}