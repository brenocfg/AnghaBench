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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int cpCRreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_VIRTUAL_TO_PHYSICAL (void*) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int _SHIFTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  __GX_FifoReadDisable () ; 
 int /*<<< orphan*/  __GX_FifoReadEnable () ; 
 TYPE_1__* __gx ; 
 int* _cpReg ; 
 void* _gxcurrbp ; 

void GX_EnableBreakPt(void *break_pt)
{
	u32 level = 0;
	_CPU_ISR_Disable(level);
	__GX_FifoReadDisable();
	_cpReg[30] = _SHIFTL(MEM_VIRTUAL_TO_PHYSICAL(break_pt),0,16);
	_cpReg[31] = _SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(break_pt),16,16);
	__gx->cpCRreg = (__gx->cpCRreg&~0x22)|0x22;
	_cpReg[1] = __gx->cpCRreg;
	_gxcurrbp = break_pt;
	__GX_FifoReadEnable();
 	_CPU_ISR_Restore(level);
}