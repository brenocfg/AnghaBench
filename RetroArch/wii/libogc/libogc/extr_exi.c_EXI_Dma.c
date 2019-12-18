#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t s32 ;
struct TYPE_3__ {int flags; scalar_t__ imm_len; int /*<<< orphan*/ * imm_buff; scalar_t__ CallbackTC; } ;
typedef  TYPE_1__ exibus_priv ;
typedef  scalar_t__ EXICallback ;

/* Variables and functions */
 int EXI_FLAG_DMA ; 
 int EXI_FLAG_IMM ; 
 int EXI_FLAG_SELECT ; 
 int /*<<< orphan*/  IRQMASK (scalar_t__) ; 
 scalar_t__ IRQ_EXI0_TC ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __exi_clearirqs (size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int* _exiReg ; 
 TYPE_1__* eximap ; 

s32 EXI_Dma(s32 nChn,void *pData,u32 nLen,u32 nMode,EXICallback tc_cb)
{
	u32 level;
	exibus_priv *exi = &eximap[nChn];
	_CPU_ISR_Disable(level);

	if(exi->flags&(EXI_FLAG_DMA|EXI_FLAG_IMM) || !(exi->flags&EXI_FLAG_SELECT)) {
		_CPU_ISR_Restore(level);
		return 0;
	}
	exi->CallbackTC = tc_cb;
	if(tc_cb) {
		__exi_clearirqs(nChn,0,1,0);
		__UnmaskIrq((IRQMASK((IRQ_EXI0_TC+(nChn*3)))));
	}

	exi->imm_buff = NULL;
	exi->imm_len = 0;
	exi->flags |= EXI_FLAG_DMA;

	_exiReg[nChn*5+1] = (u32)pData&0x03FFFFE0;
	_exiReg[nChn*5+2] = nLen;
	_exiReg[nChn*5+3] = ((nMode&0x03)<<2)|0x03;

	_CPU_ISR_Restore(level);
	return 1;
}