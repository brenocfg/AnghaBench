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
typedef  size_t s32 ;

/* Variables and functions */
 int PAD_ENABLEDMASK (size_t) ; 
 int SI_GetType (size_t) ; 
 int __pad_analogmode ; 
 int** __pad_origin ; 
 int __pad_xpatchbits ; 

__attribute__((used)) static void __pad_updateorigin(s32 chan)
{
	u32 mode,mask,type;

	mask = PAD_ENABLEDMASK(chan);
	mode = __pad_analogmode&0x0700;
	if(mode==0x0100) {
		__pad_origin[chan][4] &= ~0x0f;
		__pad_origin[chan][5] &= ~0x0f;
		__pad_origin[chan][8] &= ~0x0f;
		__pad_origin[chan][9] &= ~0x0f;
	} else if(mode==0x200) {
		__pad_origin[chan][4] &= ~0x0f;
		__pad_origin[chan][5] &= ~0x0f;
		__pad_origin[chan][6] &= ~0x0f;
		__pad_origin[chan][7] &= ~0x0f;
	}

	__pad_origin[chan][2] -= 128;
	__pad_origin[chan][3] -= 128;
	__pad_origin[chan][4] -= 128;
	__pad_origin[chan][5] -= 128;

	if(__pad_xpatchbits&mask && (s32)__pad_origin[chan][2]>64) {
		type = SI_GetType(chan)&~0xffff;
		if(!(type&~0x09ffffff)) __pad_origin[chan][2] = 0;
	}
}