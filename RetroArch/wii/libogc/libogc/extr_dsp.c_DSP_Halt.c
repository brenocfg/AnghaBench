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
typedef  int u32 ;

/* Variables and functions */
 int DSPCR_AIINT ; 
 int DSPCR_ARINT ; 
 int DSPCR_DSPINT ; 
 int DSPCR_HALT ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int* _dspReg ; 

void DSP_Halt()
{
	u32 level,old;

	_CPU_ISR_Disable(level);
	old = _dspReg[5];
	_dspReg[5] = (old&~(DSPCR_AIINT|DSPCR_ARINT|DSPCR_DSPINT))|DSPCR_HALT;
	_CPU_ISR_Restore(level);
}