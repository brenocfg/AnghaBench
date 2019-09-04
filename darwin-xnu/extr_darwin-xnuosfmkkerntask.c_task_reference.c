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
typedef  scalar_t__ task_t ;

/* Variables and functions */
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  task_reference_internal (scalar_t__) ; 

void
task_reference(
	task_t		task)
{
	if (task != TASK_NULL)
		task_reference_internal(task);
}