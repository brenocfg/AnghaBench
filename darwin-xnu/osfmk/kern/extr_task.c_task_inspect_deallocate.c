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
typedef  scalar_t__ task_inspect_t ;

/* Variables and functions */
 void task_deallocate (int /*<<< orphan*/ ) ; 

void
task_inspect_deallocate(
	task_inspect_t		task_inspect)
{
	return(task_deallocate((task_t)task_inspect));
}