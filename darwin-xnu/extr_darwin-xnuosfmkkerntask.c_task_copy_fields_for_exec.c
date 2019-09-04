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
typedef  TYPE_1__* task_t ;
struct TYPE_4__ {int /*<<< orphan*/  vtimers; } ;

/* Variables and functions */

void
task_copy_fields_for_exec(task_t dst_task, task_t src_task)
{
	dst_task->vtimers = src_task->vtimers;
}