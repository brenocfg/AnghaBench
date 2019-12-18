#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ dsptask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSPTASK_CLEARALL ; 
 int /*<<< orphan*/  DSPTASK_DONE ; 
 TYPE_1__* __dsp_currtask ; 
 TYPE_1__* __dsp_firsttask ; 
 TYPE_1__* __dsp_lasttask ; 

__attribute__((used)) static void __dsp_removetask(dsptask_t *task)
{
	task->flags = DSPTASK_CLEARALL;
	task->state = DSPTASK_DONE;
	if(__dsp_firsttask==task) {
		if(task->next) {
			__dsp_firsttask = task->next;
			__dsp_firsttask->prev = NULL;
			return;
		}
		__dsp_currtask = NULL;
		__dsp_lasttask = NULL;
		__dsp_firsttask = NULL;
		return;
	}
	if(__dsp_lasttask==task) {
		__dsp_lasttask = task->prev;
		__dsp_lasttask->next = NULL;
		__dsp_currtask = __dsp_firsttask;
		return;
	}
	__dsp_currtask = __dsp_currtask->next;
}