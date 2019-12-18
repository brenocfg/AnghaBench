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

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int _SHIFTR (int,int,int) ; 
 int* _dspReg ; 

void AUDIO_InitDMA(u32 startaddr,u32 len)
{
	u32 level;

	_CPU_ISR_Disable(level);
	_dspReg[24] = (_dspReg[24]&~0x1fff)|(_SHIFTR(startaddr,16,13));
	_dspReg[25] = (_dspReg[25]&~0xffe0)|(startaddr&0xffff);
	_dspReg[27] = (_dspReg[27]&~0x7fff)|(_SHIFTR(len,5,15));
	_CPU_ISR_Restore(level);
}