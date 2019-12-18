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
struct pci_controller {int /*<<< orphan*/  cfg_data; } ;
typedef  int /*<<< orphan*/  PCI_IO_ADDR ;

/* Variables and functions */

__attribute__((used)) static inline PCI_IO_ADDR celleb_epci_get_epci_cfg(
					struct pci_controller *hose)
{
	/*
	 * Note:
	 * Celleb epci uses cfg_data as a base address for
	 * configuration area for epci devices.
	 */

	return hose->cfg_data;
}