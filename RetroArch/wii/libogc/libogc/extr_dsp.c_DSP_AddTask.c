#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ dsptask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSPTASK_ATTACH ; 
 int /*<<< orphan*/  DSPTASK_INIT ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dsp_boottask (TYPE_1__*) ; 
 TYPE_1__* __dsp_firsttask ; 
 int /*<<< orphan*/  __dsp_inserttask (TYPE_1__*) ; 

dsptask_t* DSP_AddTask(dsptask_t *task)
{
	u32 level;
	_CPU_ISR_Disable(level);
	__dsp_inserttask(task);
	task->state = DSPTASK_INIT;
	task->flags = DSPTASK_ATTACH;
	_CPU_ISR_Restore(level);

	if(__dsp_firsttask==task) __dsp_boottask(task);
	return task;
}