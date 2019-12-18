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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ prio; scalar_t__ state; } ;
typedef  TYPE_1__ dsptask_t ;

/* Variables and functions */
 int DSPCR_AIINT ; 
 int DSPCR_ARINT ; 
 int DSPCR_DSPINT ; 
 int DSPCR_PIINT ; 
 scalar_t__ DSPTASK_RUN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 TYPE_1__* __dsp_currtask ; 
 TYPE_1__* __dsp_rudetask ; 
 int /*<<< orphan*/  __dsp_rudetask_pend ; 
 int* _dspReg ; 

dsptask_t* DSP_AssertTask(dsptask_t *task)
{
	u32 level;
	dsptask_t *ret = NULL;

	_CPU_ISR_Disable(level);
	if(task==__dsp_currtask) {
		__dsp_rudetask = task;
		__dsp_rudetask_pend = TRUE;
		ret = task;
	} else {
		if(task->prio<__dsp_currtask->prio) {
			__dsp_rudetask = task;
			__dsp_rudetask_pend = TRUE;
			if(__dsp_currtask->state==DSPTASK_RUN)
				_dspReg[5] = ((_dspReg[5]&~(DSPCR_DSPINT|DSPCR_ARINT|DSPCR_AIINT))|DSPCR_PIINT);

			ret = task;
		}
	}
	_CPU_ISR_Restore(level);

	return ret;
}