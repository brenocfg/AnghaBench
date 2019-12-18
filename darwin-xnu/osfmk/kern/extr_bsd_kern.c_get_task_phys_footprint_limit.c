#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  ledger_amount_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_5__ {int /*<<< orphan*/  phys_footprint; } ;
struct TYPE_4__ {int /*<<< orphan*/  ledger; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ ledger_get_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ task_ledgers ; 

uint64_t get_task_phys_footprint_limit(task_t task)
{
	kern_return_t ret;
	ledger_amount_t max;

	ret = ledger_get_limit(task->ledger, task_ledgers.phys_footprint, &max);
	if (KERN_SUCCESS == ret) {
		return max;
	}

	return 0;
}