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
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */

__attribute__((used)) static uintptr_t
trequested_1(task_t task)
{
#if defined __LP64__
	(void)task;
	return 0;
#else
	uintptr_t* raw = (uintptr_t*)(&task->requested_policy);
	return raw[1];
#endif
}