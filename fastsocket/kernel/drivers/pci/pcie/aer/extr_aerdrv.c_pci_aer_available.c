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
 scalar_t__ pci_msi_enabled () ; 
 int /*<<< orphan*/  pcie_aer_disable ; 

bool pci_aer_available(void)
{
	return !pcie_aer_disable && pci_msi_enabled();
}