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
struct TYPE_2__ {int size; int /*<<< orphan*/  total_size; int /*<<< orphan*/  io_addr; } ;
struct be_adapter {int /*<<< orphan*/  pdev; TYPE_1__ roce_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_bar (struct be_adapter*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skyhawk_chip (struct be_adapter*) ; 

__attribute__((used)) static int be_roce_map_pci_bars(struct be_adapter *adapter)
{
	if (skyhawk_chip(adapter)) {
		adapter->roce_db.size = 4096;
		adapter->roce_db.io_addr = pci_resource_start(adapter->pdev,
							      db_bar(adapter));
		adapter->roce_db.total_size = pci_resource_len(adapter->pdev,
							       db_bar(adapter));
	}
	return 0;
}