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

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 int* _dspReg ; 

void AR_StartDMA(u32 dir,u32 memaddr,u32 aramaddr,u32 len)
{
	u32 level;

	_CPU_ISR_Disable(level);

	// set main memory address
	_dspReg[16] = (_dspReg[16]&~0x03ff)|_SHIFTR(memaddr,16,16);
	_dspReg[17] = (_dspReg[17]&~0xffe0)|_SHIFTR(memaddr, 0,16);

	// set aram address
	_dspReg[18] = (_dspReg[18]&~0x03ff)|_SHIFTR(aramaddr,16,16);
	_dspReg[19] = (_dspReg[19]&~0xffe0)|_SHIFTR(aramaddr, 0,16);

	// set cntrl bits
	_dspReg[20] = (_dspReg[20]&~0x8000)|_SHIFTL(dir,15,1);
	_dspReg[20] = (_dspReg[20]&~0x03ff)|_SHIFTR(len,16,16);
	_dspReg[21] = (_dspReg[21]&~0xffe0)|_SHIFTR(len, 0,16);

	_CPU_ISR_Restore(level);
}