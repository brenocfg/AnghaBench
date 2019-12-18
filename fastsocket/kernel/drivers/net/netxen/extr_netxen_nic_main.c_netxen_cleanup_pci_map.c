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
struct TYPE_2__ {int /*<<< orphan*/ * pci_base2; int /*<<< orphan*/ * pci_base1; int /*<<< orphan*/ * pci_base0; int /*<<< orphan*/ * db_base; } ;
struct netxen_adapter {TYPE_1__ ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
netxen_cleanup_pci_map(struct netxen_adapter *adapter)
{
	if (adapter->ahw.db_base != NULL)
		iounmap(adapter->ahw.db_base);
	if (adapter->ahw.pci_base0 != NULL)
		iounmap(adapter->ahw.pci_base0);
	if (adapter->ahw.pci_base1 != NULL)
		iounmap(adapter->ahw.pci_base1);
	if (adapter->ahw.pci_base2 != NULL)
		iounmap(adapter->ahw.pci_base2);
}