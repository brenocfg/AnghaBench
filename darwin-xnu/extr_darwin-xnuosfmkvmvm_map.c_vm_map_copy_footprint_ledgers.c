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
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_2__ {int /*<<< orphan*/  wired_mem; int /*<<< orphan*/  network_nonvolatile_compressed; int /*<<< orphan*/  network_nonvolatile; int /*<<< orphan*/  page_table; int /*<<< orphan*/  alternate_accounting_compressed; int /*<<< orphan*/  alternate_accounting; int /*<<< orphan*/  iokit_mapped; int /*<<< orphan*/  internal_compressed; int /*<<< orphan*/  internal; int /*<<< orphan*/  purgeable_nonvolatile_compressed; int /*<<< orphan*/  purgeable_nonvolatile; int /*<<< orphan*/  phys_footprint; } ;

/* Variables and functions */
 TYPE_1__ task_ledgers ; 
 int /*<<< orphan*/  vm_map_copy_ledger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_map_copy_footprint_ledgers(
	task_t	old_task,
	task_t	new_task)
{
	vm_map_copy_ledger(old_task, new_task, task_ledgers.phys_footprint);
	vm_map_copy_ledger(old_task, new_task, task_ledgers.purgeable_nonvolatile);
	vm_map_copy_ledger(old_task, new_task, task_ledgers.purgeable_nonvolatile_compressed);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.internal);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.internal_compressed);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.iokit_mapped);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.alternate_accounting);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.alternate_accounting_compressed);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.page_table);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.network_nonvolatile);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.network_nonvolatile_compressed);
    vm_map_copy_ledger(old_task, new_task, task_ledgers.wired_mem);
}