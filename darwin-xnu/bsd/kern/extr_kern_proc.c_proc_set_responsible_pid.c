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
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_responsible_pid; } ;

/* Variables and functions */

void proc_set_responsible_pid(proc_t target_proc, pid_t responsible_pid)
{
	if (target_proc != NULL) {
		target_proc->p_responsible_pid = responsible_pid;
	}
	return;
}