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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/ * task_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_task_memory_region_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
memorystatus_get_task_memory_region_count(task_t task, uint64_t *count)
{
	assert(task);
	assert(count);

	*count = get_task_memory_region_count(task);
}