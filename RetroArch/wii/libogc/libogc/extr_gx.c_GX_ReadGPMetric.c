#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ perf0Mode; } ;

/* Variables and functions */
 scalar_t__ GX_PERF0_CLIP_RATIO ; 
 scalar_t__ GX_PERF0_NONE ; 
 scalar_t__ GX_PERF0_VERTICES ; 
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* __gx ; 
 int* _cpReg ; 

void GX_ReadGPMetric(u32 *cnt0,u32 *cnt1)
{
	u32 tmp,reg1,reg2;

	reg1 = (_SHIFTL(_cpReg[33],16,16))|(_cpReg[32]&0xffff);
	reg2 = (_SHIFTL(_cpReg[35],16,16))|(_cpReg[34]&0xffff);
	//reg3 = (_SHIFTL(_cpReg[37],16,16))|(_cpReg[36]&0xffff);
	//reg4 = (_SHIFTL(_cpReg[39],16,16))|(_cpReg[38]&0xffff);

	*cnt0 = 0;
	if(__gx->perf0Mode==GX_PERF0_CLIP_RATIO) {
		tmp = reg2*1000;
		*cnt0 = tmp/reg1;
	} else if(__gx->perf0Mode>=GX_PERF0_VERTICES && __gx->perf0Mode<GX_PERF0_NONE) *cnt0 = reg1;

	//further implementation needed.....
	// cnt1 fails....
}