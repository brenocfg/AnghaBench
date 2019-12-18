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
struct __gxfifo {int wt_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_DISABLE ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  IsWriteGatherBufferEmpty () ; 
 scalar_t__ MEM_PHYSICAL_TO_K0 (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/  __GX_FifoLink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cpgplinked ; 
 int /*<<< orphan*/  _cpufifo ; 
 int* _piReg ; 
 int /*<<< orphan*/  _sync () ; 
 int /*<<< orphan*/  mtwpar (int) ; 

volatile void* GX_RedirectWriteGatherPipe(void *ptr)
{
	u32 level;
	struct __gxfifo *cpufifo = (struct __gxfifo*)&_cpufifo;

	_CPU_ISR_Disable(level);
	GX_Flush();
	while(!IsWriteGatherBufferEmpty());

	mtwpar(0x0C008000);
	if(_cpgplinked) {
		__GX_FifoLink(GX_FALSE);
		__GX_WriteFifoIntEnable(GX_DISABLE,GX_DISABLE);
	}
	cpufifo->wt_ptr = (u32)MEM_PHYSICAL_TO_K0(_piReg[5]&~0x04000000);

	_piReg[3] = 0;
	_piReg[4] = 0x04000000;
	_piReg[5] = (((u32)ptr&0x3FFFFFE0)&~0x04000000);
	_sync();

	_CPU_ISR_Restore(level);

	return (volatile void*)0x0C008000;
}