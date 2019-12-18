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
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;
struct pci_controller {TYPE_1__ io_resource; scalar_t__ pci_io_size; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */

__attribute__((used)) static resource_size_t pcibios_io_size(const struct pci_controller *hose)
{
#ifdef CONFIG_PPC64
	return hose->pci_io_size;
#else
	return hose->io_resource.end - hose->io_resource.start + 1;
#endif
}