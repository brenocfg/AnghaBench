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
struct TYPE_3__ {scalar_t__ iobase; scalar_t__ membase; int /*<<< orphan*/  pdev; } ;
typedef  TYPE_1__ hfc4s8s_hw ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void
release_pci_ports(hfc4s8s_hw * hw)
{
	pci_write_config_word(hw->pdev, PCI_COMMAND, 0);
#ifdef HISAX_HFC4S8S_PCIMEM
	if (hw->membase)
		iounmap((void *) hw->membase);
#else
	if (hw->iobase)
		release_region(hw->iobase, 8);
#endif
}