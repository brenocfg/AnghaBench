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
typedef  int u16 ;

/* Variables and functions */
 int DSPCR_AIINT ; 
 int DSPCR_ARINT ; 
 int DSPCR_DSPINT ; 
 int* _dspReg ; 

__attribute__((used)) static __inline__ void __ARClearInterrupt()
{
	u16 cause;

	cause = _dspReg[5]&~(DSPCR_DSPINT|DSPCR_AIINT);
	_dspReg[5] = (cause|DSPCR_ARINT);
}