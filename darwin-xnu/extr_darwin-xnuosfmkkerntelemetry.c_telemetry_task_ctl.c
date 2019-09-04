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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  telemetry_task_ctl_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
telemetry_task_ctl(task_t task, uint32_t reasons, int enable_disable)
{
	task_lock(task);
	telemetry_task_ctl_locked(task, reasons, enable_disable);
	task_unlock(task);
}