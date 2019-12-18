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
typedef  int u8 ;
typedef  size_t u32 ;
struct TYPE_2__ {int* tevSwapModeTable; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 
 size_t _SHIFTR (int,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetTevKAlphaSel(u8 tevstage,u8 sel)
{
	u32 reg = (_SHIFTR(tevstage,1,3));

	if(tevstage&1)
		__gx->tevSwapModeTable[reg] = (__gx->tevSwapModeTable[reg]&~0xF80000)|(_SHIFTL(sel,19,5));
	else
		__gx->tevSwapModeTable[reg] = (__gx->tevSwapModeTable[reg]&~0x3E00)|(_SHIFTL(sel,9,5));
	GX_LOAD_BP_REG(__gx->tevSwapModeTable[reg]);
}