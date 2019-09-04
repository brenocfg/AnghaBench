#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_3__ {int /*<<< orphan*/  crashed_thread_id; } ;

/* Variables and functions */

uint64_t
task_corpse_get_crashed_thread_id(task_t corpse_task)
{
	return corpse_task->crashed_thread_id;
}