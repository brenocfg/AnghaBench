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
typedef  int /*<<< orphan*/  u8 ;
struct pci_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scc_pciex_read_port (struct pci_controller*,unsigned long,int) ; 

__attribute__((used)) static u8 __scc_pciex_inb(struct pci_controller *phb, unsigned long port)
{
	return (u8)scc_pciex_read_port(phb, port, 1);
}