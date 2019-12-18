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
typedef  TYPE_1__* task_t ;
struct TYPE_3__ {int /*<<< orphan*/  t_procflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPF_DID_EXEC ; 

void
task_set_did_exec_flag(task_t task)
{
	task->t_procflags |= TPF_DID_EXEC;
}