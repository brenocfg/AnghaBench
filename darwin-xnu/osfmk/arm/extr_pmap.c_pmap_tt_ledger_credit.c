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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ pmap_t ;
struct TYPE_2__ {int /*<<< orphan*/  page_table; int /*<<< orphan*/  phys_footprint; } ;

/* Variables and functions */
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  pmap_ledger_credit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ task_ledgers ; 

__attribute__((used)) static inline void
pmap_tt_ledger_credit(
	pmap_t		pmap,
	vm_size_t	size)
{
	if (pmap != kernel_pmap) {
		pmap_ledger_credit(pmap, task_ledgers.phys_footprint, size);
		pmap_ledger_credit(pmap, task_ledgers.page_table, size);
	}
}