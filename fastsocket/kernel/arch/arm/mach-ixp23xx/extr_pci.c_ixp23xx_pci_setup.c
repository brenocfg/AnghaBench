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
struct pci_sys_data {int /*<<< orphan*/ ** resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixp23xx_pci_io_space ; 
 int /*<<< orphan*/  ixp23xx_pci_mem_space ; 

int ixp23xx_pci_setup(int nr, struct pci_sys_data *sys)
{
	if (nr >= 1)
		return 0;

	sys->resource[0] = &ixp23xx_pci_io_space;
	sys->resource[1] = &ixp23xx_pci_mem_space;
	sys->resource[2] = NULL;

	return 1;
}