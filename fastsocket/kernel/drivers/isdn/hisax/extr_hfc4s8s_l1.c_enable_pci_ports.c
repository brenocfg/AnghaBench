#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;
typedef  TYPE_1__ hfc4s8s_hw ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_ENA_MEMIO ; 
 int /*<<< orphan*/  PCI_ENA_REGIO ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_pci_ports(hfc4s8s_hw * hw)
{
#ifdef HISAX_HFC4S8S_PCIMEM
	pci_write_config_word(hw->pdev, PCI_COMMAND, PCI_ENA_MEMIO);
#else
	pci_write_config_word(hw->pdev, PCI_COMMAND, PCI_ENA_REGIO);
#endif
}