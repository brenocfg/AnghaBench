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
typedef  int /*<<< orphan*/  xstate_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_4__ {int /*<<< orphan*/  xstate; } ;

/* Variables and functions */
 TYPE_1__* TASK_NULL ; 
 int /*<<< orphan*/  fpu_default ; 

__attribute__((used)) static xstate_t
task_xstate(task_t task)
{
	if (task == TASK_NULL)
		return fpu_default;
	else
		return task->xstate;
}