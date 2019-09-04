#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_5__ {int /*<<< orphan*/  phys_footprint; int /*<<< orphan*/  iokit_mapped; } ;
struct TYPE_4__ {int /*<<< orphan*/  ledger; } ;

/* Variables and functions */
 int /*<<< orphan*/  ledger_credit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ task_ledgers ; 
 TYPE_1__* vm_map_pmap (int /*<<< orphan*/ ) ; 

void
vm_map_iokit_mapped_region(vm_map_t map, vm_size_t bytes)
{
	pmap_t pmap = vm_map_pmap(map);

	ledger_credit(pmap->ledger, task_ledgers.iokit_mapped, bytes);
	ledger_credit(pmap->ledger, task_ledgers.phys_footprint, bytes);
}