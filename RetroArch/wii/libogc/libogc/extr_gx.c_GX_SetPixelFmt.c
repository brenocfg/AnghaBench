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
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_2__ {int peCntrl; int dirtyState; int genMode; int peCMode1; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 size_t GX_PF_RGB565_Z16 ; 
 int GX_PF_Y8 ; 
 int _SHIFTL (size_t,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetPixelFmt(u8 pix_fmt,u8 z_fmt)
{
	u8 ms_en = 0;
	u32 realfmt[8] = {0,1,2,3,4,4,4,5};

	__gx->peCntrl = (__gx->peCntrl&~0x7)|(realfmt[pix_fmt]&0x7);
	__gx->peCntrl = (__gx->peCntrl&~0x38)|(_SHIFTL(z_fmt,3,3));
	GX_LOAD_BP_REG(__gx->peCntrl);
	__gx->dirtyState |= 0x0004;

	if(pix_fmt==GX_PF_RGB565_Z16) ms_en = 1;
	__gx->genMode = (__gx->genMode&~0x200)|(_SHIFTL(ms_en,9,1));

	if(realfmt[pix_fmt]==GX_PF_Y8) {
		pix_fmt -= GX_PF_Y8;
		__gx->peCMode1 = (__gx->peCMode1&~0xC00)|(_SHIFTL(pix_fmt,10,2));
		GX_LOAD_BP_REG(__gx->peCMode1);
	}
}