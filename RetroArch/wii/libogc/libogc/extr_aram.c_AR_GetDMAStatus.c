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
 int DSPCR_DSPDMA ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int* _dspReg ; 

u32 AR_GetDMAStatus()
{
	u32 level,ret;
	_CPU_ISR_Disable(level);
	ret = ((_dspReg[5]&DSPCR_DSPDMA)==DSPCR_DSPDMA);
	_CPU_ISR_Restore(level);
	return ret;
}