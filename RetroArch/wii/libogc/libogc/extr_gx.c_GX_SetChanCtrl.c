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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int s32 ;
struct TYPE_2__ {size_t* chnCntrl; int dirtyState; } ;

/* Variables and functions */
 scalar_t__ GX_AF_NONE ; 
 scalar_t__ GX_AF_SPEC ; 
 int GX_COLOR0A0 ; 
 scalar_t__ GX_DF_NONE ; 
 scalar_t__ _SHIFTL (int,int,int) ; 
 int _SHIFTR (scalar_t__,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetChanCtrl(s32 channel,u8 enable,u8 ambsrc,u8 matsrc,u8 litmask,u8 diff_fn,u8 attn_fn)
{
	u32 reg,difffn = (attn_fn==GX_AF_SPEC)?GX_DF_NONE:diff_fn;
	u32 val = (matsrc&1)|(_SHIFTL(enable,1,1))|(_SHIFTL(litmask,2,4))|(_SHIFTL(ambsrc,6,1))|(_SHIFTL(difffn,7,2))|(_SHIFTL(((GX_AF_NONE-attn_fn)>0),9,1))|(_SHIFTL((attn_fn>0),10,1))|(_SHIFTL((_SHIFTR(litmask,4,4)),11,4));

	reg = (channel&0x03);
	__gx->chnCntrl[reg] = val;
	__gx->dirtyState |= (0x1000<<reg);

	if(channel==GX_COLOR0A0) {
		__gx->chnCntrl[2] = val;
		__gx->dirtyState |= 0x5000;
	} else {
		__gx->chnCntrl[3] = val;
		__gx->dirtyState |= 0xa000;
	}
}