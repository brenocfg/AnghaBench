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
struct __gxfifo {int wt_ptr; int fifo_wrap; int rd_ptr; int rdwt_dst; int size; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ MEM_PHYSICAL_TO_K0 (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int _SHIFTL (int,int,int) ; 
 int* _cpReg ; 
 scalar_t__ _cpgplinked ; 
 int /*<<< orphan*/  _cpufifo ; 
 int /*<<< orphan*/  _gpfifo ; 
 scalar_t__ _gxcpufifoready ; 
 scalar_t__ _gxgpfifoready ; 
 int* _piReg ; 

__attribute__((used)) static void __GX_SaveFifo()
{
	s32 rdwt_dst;
	u32 level,val;
	struct __gxfifo *cpufifo = (struct __gxfifo*)&_cpufifo;
	struct __gxfifo *gpfifo = (struct __gxfifo*)&_gpfifo;

	_CPU_ISR_Disable(level);

	if(_gxcpufifoready) {
		val = _piReg[0x05];
		cpufifo->wt_ptr = (u32)MEM_PHYSICAL_TO_K0((val&0x1FFFFFE0));
		cpufifo->fifo_wrap = ((val&0x20000000)==0x20000000);
	}

	if(_gxgpfifoready) {
		gpfifo->rd_ptr = (u32)MEM_PHYSICAL_TO_K0(_SHIFTL(_cpReg[29],16,16)|(_cpReg[28]&0xffff));
		gpfifo->rdwt_dst = (_SHIFTL(_cpReg[25],16,16)|(_cpReg[24]&0xffff));
	}

	if(_cpgplinked) {
		cpufifo->rd_ptr = gpfifo->rd_ptr;
		cpufifo->rdwt_dst = gpfifo->rdwt_dst;
		gpfifo->wt_ptr = cpufifo->wt_ptr;
	} else if(_gxcpufifoready) {
		rdwt_dst = (cpufifo->wt_ptr - cpufifo->rd_ptr);
		if(rdwt_dst<0) cpufifo->rdwt_dst = (cpufifo->rdwt_dst + cpufifo->size);
		else cpufifo->rdwt_dst = rdwt_dst;
	}

	_CPU_ISR_Restore(level);
}