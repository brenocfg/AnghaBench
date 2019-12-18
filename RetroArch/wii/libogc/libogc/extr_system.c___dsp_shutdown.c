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
 int DSPCR_DSPRESET ; 
 int DSPCR_HALT ; 
 int DSPCR_RES ; 
 int _SHIFTL (int,int,int) ; 
 int* _dspReg ; 
 int gettick () ; 

__attribute__((used)) static void __dsp_shutdown()
{
	u32 tick;

	_dspReg[5] = (DSPCR_DSPRESET|DSPCR_HALT);
	_dspReg[27] &= ~0x8000;
	while(_dspReg[5]&0x400);
	while(_dspReg[5]&0x200);

	_dspReg[5] = (DSPCR_DSPRESET|DSPCR_DSPINT|DSPCR_ARINT|DSPCR_AIINT|DSPCR_HALT);
	_dspReg[0] = 0;
	while((_SHIFTL(_dspReg[2],16,16)|(_dspReg[3]&0xffff))&0x80000000);

	tick = gettick();
	while((gettick()-tick)<44);

	_dspReg[5] |= DSPCR_RES;
	while(_dspReg[5]&DSPCR_RES);
}