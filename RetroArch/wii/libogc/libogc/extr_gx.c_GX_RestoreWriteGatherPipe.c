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
struct __gxfifo {scalar_t__ wt_ptr; int /*<<< orphan*/  buf_end; int /*<<< orphan*/  buf_start; } ;
struct TYPE_2__ {scalar_t__ U32; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_DISABLE ; 
 int /*<<< orphan*/  GX_ENABLE ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  IsWriteGatherBufferEmpty () ; 
 int MEM_VIRTUAL_TO_PHYSICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/  __GX_FifoLink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cpgplinked ; 
 int /*<<< orphan*/  _cpufifo ; 
 int* _piReg ; 
 int /*<<< orphan*/  mtwpar (int) ; 
 int /*<<< orphan*/  ppcsync () ; 
 TYPE_1__* wgPipe ; 

void GX_RestoreWriteGatherPipe()
{
	u32 level;
	struct __gxfifo *cpufifo = (struct __gxfifo*)&_cpufifo;

	_CPU_ISR_Disable(level);

	wgPipe->U32 = 0;
	wgPipe->U32 = 0;
	wgPipe->U32 = 0;
	wgPipe->U32 = 0;
	wgPipe->U32 = 0;
	wgPipe->U32 = 0;
	wgPipe->U32 = 0;
	wgPipe->U32 = 0;

	ppcsync();
	while(!IsWriteGatherBufferEmpty());

	mtwpar(0x0C008000);
	_piReg[3] = MEM_VIRTUAL_TO_PHYSICAL(cpufifo->buf_start);
	_piReg[4] = MEM_VIRTUAL_TO_PHYSICAL(cpufifo->buf_end);
	_piReg[5] = (((u32)cpufifo->wt_ptr&0x3FFFFFE0)&~0x04000000);
	if(_cpgplinked) {
		__GX_WriteFifoIntReset(GX_TRUE,GX_TRUE);
		__GX_WriteFifoIntEnable(GX_ENABLE,GX_DISABLE);
		__GX_FifoLink(GX_TRUE);
	}
	_CPU_ISR_Restore(level);
}