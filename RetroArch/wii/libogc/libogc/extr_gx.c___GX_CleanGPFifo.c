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
struct __gxfifo {int rd_ptr; int wt_ptr; scalar_t__ rdwt_dst; } ;
struct TYPE_2__ {int cpCRreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MEM_VIRTUAL_TO_PHYSICAL (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int _SHIFTL (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int _SHIFTR (scalar_t__,int,int) ; 
 int /*<<< orphan*/  __GX_FifoLink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_FifoReadDisable () ; 
 int /*<<< orphan*/  __GX_FifoReadEnable () ; 
 int /*<<< orphan*/  __GX_WriteFifoIntEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* __gx ; 
 int* _cpReg ; 
 scalar_t__ _cpgplinked ; 
 int /*<<< orphan*/  _cpufifo ; 
 int /*<<< orphan*/  _gpfifo ; 
 int /*<<< orphan*/  _gxgpfifoready ; 
 int* _piReg ; 
 int /*<<< orphan*/ * breakPtCB ; 
 int /*<<< orphan*/  ppcsync () ; 

__attribute__((used)) static void __GX_CleanGPFifo()
{
	u32 level;
	struct __gxfifo *gpfifo = (struct __gxfifo*)&_gpfifo;
	struct __gxfifo *cpufifo = (struct __gxfifo*)&_cpufifo;

	if(!_gxgpfifoready) return;

	_CPU_ISR_Disable(level);
	__GX_FifoReadDisable();
	__GX_WriteFifoIntEnable(FALSE,FALSE);

	gpfifo->rd_ptr = gpfifo->wt_ptr;
	gpfifo->rdwt_dst = 0;

	/* setup rd<->wd dist */
	_cpReg[24] = _SHIFTL(gpfifo->rdwt_dst,0,16);
	_cpReg[25] = _SHIFTR(gpfifo->rdwt_dst,16,16);

	/* setup wt ptr */
	_cpReg[26] = _SHIFTL(MEM_VIRTUAL_TO_PHYSICAL(gpfifo->wt_ptr),0,16);
	_cpReg[27] = _SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(gpfifo->wt_ptr),16,16);

	/* setup rd ptr */
	_cpReg[28] = _SHIFTL(MEM_VIRTUAL_TO_PHYSICAL(gpfifo->rd_ptr),0,16);
	_cpReg[29] = _SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(gpfifo->rd_ptr),16,16);
	ppcsync();

	if(_cpgplinked) {
		cpufifo->rd_ptr = gpfifo->rd_ptr;
		cpufifo->wt_ptr = gpfifo->wt_ptr;
		cpufifo->rdwt_dst = gpfifo->rdwt_dst;

		_piReg[5] = (cpufifo->wt_ptr&0x1FFFFFE0);
		__GX_WriteFifoIntEnable(TRUE,FALSE);
		__GX_FifoLink(TRUE);
	}
	__gx->cpCRreg &= ~0x22;
	_cpReg[1] = __gx->cpCRreg;
	breakPtCB = NULL;

	__GX_WriteFifoIntReset(TRUE,TRUE);
	__GX_FifoReadEnable();
	_CPU_ISR_Restore(level);
}