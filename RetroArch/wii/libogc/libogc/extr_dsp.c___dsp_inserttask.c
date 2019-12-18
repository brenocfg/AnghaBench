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
struct TYPE_6__ {scalar_t__ prio; struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_1__ dsptask_t ;

/* Variables and functions */
 TYPE_1__* __dsp_currtask ; 
 TYPE_1__* __dsp_firsttask ; 
 TYPE_1__* __dsp_lasttask ; 

__attribute__((used)) static void __dsp_inserttask(dsptask_t *task)
{
	dsptask_t *t;

	if(!__dsp_firsttask) {
		__dsp_currtask = task;
		__dsp_lasttask = task;
		__dsp_firsttask = task;
		task->next = NULL;
		task->prev = NULL;
		return;
	}

	t = __dsp_firsttask;
	while(t) {
		if(task->prio<t->prio) {
			task->prev = t->prev;
			t->prev = task;
			task->next = t;
			if(!task->prev) {
				__dsp_firsttask = task;
				break;
			} else {
				task->prev->next = task;
				break;
			}
		}
		t = t->next;
	}
	if(t) return;

	__dsp_lasttask->next = task;
	task->next = NULL;
	task->prev = __dsp_lasttask;
	__dsp_lasttask = task;
}