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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  size_t s32 ;
struct TYPE_3__ {int flags; scalar_t__ imm_len; scalar_t__* imm_buff; } ;
typedef  TYPE_1__ exibus_priv ;

/* Variables and functions */
 int EXI_FLAG_DMA ; 
 int EXI_FLAG_IMM ; 
 int EXI_FLAG_SELECT ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 
 int* _exiReg ; 
 TYPE_1__* eximap ; 

s32 EXI_Sync(s32 nChn)
{
	u8 *buf;
	s32 ret;
	u32 level,i,cnt,val;
	exibus_priv *exi = &eximap[nChn];
	while(_exiReg[nChn*5+3]&0x0001);

	_CPU_ISR_Disable(level);

	ret = 0;
	if(exi->flags&EXI_FLAG_SELECT && exi->flags&(EXI_FLAG_DMA|EXI_FLAG_IMM)) {
		if(exi->flags&EXI_FLAG_IMM) {
			cnt = exi->imm_len;
			buf = exi->imm_buff;
			if(buf && cnt>0) {
				val = _exiReg[nChn*5+4];
				for(i=0;i<cnt;i++) ((u8*)buf)[i] = (val>>((3-i)*8))&0xFF;
			}
		}
		exi->flags &= ~(EXI_FLAG_DMA|EXI_FLAG_IMM);
		ret = 1;
	}
	_CPU_ISR_Restore(level);
	return ret;
}