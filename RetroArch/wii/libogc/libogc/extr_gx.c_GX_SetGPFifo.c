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
struct __gxfifo {int cpufifo_ready; int gpfifo_ready; int /*<<< orphan*/  rd_ptr; int /*<<< orphan*/  wt_ptr; int /*<<< orphan*/  rdwt_dst; int /*<<< orphan*/  lo_mark; int /*<<< orphan*/  hi_mark; int /*<<< orphan*/  buf_end; int /*<<< orphan*/  buf_start; int /*<<< orphan*/  fifo_wrap; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */
 int /*<<< orphan*/  GX_DISABLE ; 
 int /*<<< orphan*/  GX_ENABLE ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  MEM_VIRTUAL_TO_PHYSICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SHIFTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ __GX_CPGPLinkCheck () ; 
 int /*<<< orphan*/  __GX_FifoLink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_FifoReadDisable () ; 
 int /*<<< orphan*/  __GX_FifoReadEnable () ; 
 int /*<<< orphan*/  __GX_WriteFifoIntEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _cpReg ; 
 int _cpgplinked ; 
 int /*<<< orphan*/  _gpfifo ; 
 int _gxgpfifoready ; 
 int /*<<< orphan*/  ppcsync () ; 

void GX_SetGPFifo(GXFifoObj *fifo)
{
	u32 level;
	struct __gxfifo *ptr = (struct __gxfifo*)fifo;
	struct __gxfifo *gpfifo = (struct __gxfifo*)&_gpfifo;

	_CPU_ISR_Disable(level);
	__GX_FifoReadDisable();
	__GX_WriteFifoIntEnable(GX_DISABLE,GX_DISABLE);

	if(!fifo) {
		_gxgpfifoready = 0;
		_cpgplinked = 0;
		gpfifo->cpufifo_ready = 0;
		gpfifo->gpfifo_ready = 0;
		__GX_FifoLink(GX_FALSE);
		_CPU_ISR_Restore(level);
		return;
	}

	gpfifo->buf_start = ptr->buf_start;
	gpfifo->buf_end = ptr->buf_end;
	gpfifo->size = ptr->size;
	gpfifo->hi_mark = ptr->hi_mark;
	gpfifo->lo_mark = ptr->lo_mark;
	gpfifo->rd_ptr = ptr->rd_ptr;
	gpfifo->wt_ptr = ptr->wt_ptr;
	gpfifo->rdwt_dst = ptr->rdwt_dst;
	gpfifo->fifo_wrap = ptr->fifo_wrap;
	gpfifo->cpufifo_ready = ptr->cpufifo_ready;
	gpfifo->gpfifo_ready = 1;
	_gxgpfifoready = 1;

	/* setup fifo base */
	_cpReg[16] = _SHIFTL(MEM_VIRTUAL_TO_PHYSICAL(gpfifo->buf_start),0,16);
	_cpReg[17] = _SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(gpfifo->buf_start),16,16);

	/* setup fifo end */
	_cpReg[18] = _SHIFTL(MEM_VIRTUAL_TO_PHYSICAL(gpfifo->buf_end),0,16);
	_cpReg[19] = _SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(gpfifo->buf_end),16,16);

	/* setup hiwater mark */
	_cpReg[20] = _SHIFTL(gpfifo->hi_mark,0,16);
	_cpReg[21] = _SHIFTR(gpfifo->hi_mark,16,16);

	/* setup lowater mark */
	_cpReg[22] = _SHIFTL(gpfifo->lo_mark,0,16);
	_cpReg[23] = _SHIFTR(gpfifo->lo_mark,16,16);

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

	if(__GX_CPGPLinkCheck()) {
		_cpgplinked = 1;
		gpfifo->cpufifo_ready = 1;
		__GX_WriteFifoIntEnable(GX_ENABLE,GX_DISABLE);
		__GX_FifoLink(GX_TRUE);
	} else {
		_cpgplinked = 0;
		gpfifo->cpufifo_ready = 0;
		__GX_WriteFifoIntEnable(GX_DISABLE,GX_DISABLE);
		__GX_FifoLink(GX_FALSE);
	}

	__GX_WriteFifoIntReset(GX_TRUE,GX_TRUE);
	__GX_FifoReadEnable();
	_CPU_ISR_Restore(level);
}