#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  kdp_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ task_has_64Bit_data (TYPE_1__*) ; 

boolean_t
kdp_copyin_word(
	task_t task, uint64_t addr, uint64_t *result, boolean_t try_fault, uint32_t *kdp_fault_results)
{
	if (task_has_64Bit_data(task)) {
		return kdp_copyin(task->map, addr, result, sizeof(uint64_t), try_fault, kdp_fault_results);
	} else {
		uint32_t buf;
		boolean_t r = kdp_copyin(task->map, addr, &buf, sizeof(uint32_t), try_fault, kdp_fault_results);
		*result = buf;
		return r;
	}
}