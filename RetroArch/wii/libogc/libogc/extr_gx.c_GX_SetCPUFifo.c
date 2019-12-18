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
typedef  int /*<<< orphan*/  u32 ;
struct __gxfifo {int gpfifo_ready; int cpufifo_ready; int wt_ptr; int /*<<< orphan*/  buf_end; int /*<<< orphan*/  buf_start; int /*<<< orphan*/  fifo_wrap; int /*<<< orphan*/  rdwt_dst; int /*<<< orphan*/  rd_ptr; int /*<<< orphan*/  lo_mark; int /*<<< orphan*/  hi_mark; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */
 int /*<<< orphan*/  GX_DISABLE ; 
 int /*<<< orphan*/  GX_ENABLE ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int MEM_VIRTUAL_TO_PHYSICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 scalar_t__ __GX_CPGPLinkCheck () ; 
 int /*<<< orphan*/  __GX_FifoLink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _cpgplinked ; 
 int /*<<< orphan*/  _cpufifo ; 
 int _gxcpufifoready ; 
 int* _piReg ; 
 int /*<<< orphan*/  ppcsync () ; 

void GX_SetCPUFifo(GXFifoObj *fifo)
{
	u32 level;
	struct __gxfifo *ptr = (struct __gxfifo*)fifo;
	struct __gxfifo *cpufifo = (struct __gxfifo*)&_cpufifo;

	_CPU_ISR_Disable(level);
	if(!fifo) {
		_gxcpufifoready = 0;
		_cpgplinked = 0;
		cpufifo->gpfifo_ready = 0;
		cpufifo->cpufifo_ready = 0;
		_CPU_ISR_Restore(level);
		return;
	}

	cpufifo->buf_start = ptr->buf_start;
	cpufifo->buf_end = ptr->buf_end;
	cpufifo->size = ptr->size;
	cpufifo->hi_mark = ptr->hi_mark;
	cpufifo->lo_mark = ptr->lo_mark;
	cpufifo->rd_ptr = ptr->rd_ptr;
	cpufifo->wt_ptr = ptr->wt_ptr;
	cpufifo->rdwt_dst = ptr->rdwt_dst;
	cpufifo->fifo_wrap = ptr->fifo_wrap;
	cpufifo->gpfifo_ready = ptr->gpfifo_ready;
	cpufifo->cpufifo_ready = 1;

	_gxcpufifoready = 1;
	if(__GX_CPGPLinkCheck()) {
		_cpgplinked = 1;
		cpufifo->gpfifo_ready = 1;

		_piReg[3] = MEM_VIRTUAL_TO_PHYSICAL(cpufifo->buf_start);
		_piReg[4] = MEM_VIRTUAL_TO_PHYSICAL(cpufifo->buf_end);
		_piReg[5] = (cpufifo->wt_ptr&0x1FFFFFE0);

		__GX_WriteFifoIntReset(GX_TRUE,GX_TRUE);
		__GX_WriteFifoIntEnable(GX_ENABLE,GX_DISABLE);
		__GX_FifoLink(GX_TRUE);

		_CPU_ISR_Restore(level);
		return;
	}

	if(_cpgplinked) {
		__GX_FifoLink(GX_FALSE);
		_cpgplinked = 0;
	}

	__GX_WriteFifoIntEnable(GX_DISABLE,GX_DISABLE);

	_piReg[3] = MEM_VIRTUAL_TO_PHYSICAL(cpufifo->buf_start);
	_piReg[4] = MEM_VIRTUAL_TO_PHYSICAL(cpufifo->buf_end);
	_piReg[5] = (cpufifo->wt_ptr&0x1FFFFFE0);
	ppcsync();

	_CPU_ISR_Restore(level);
}