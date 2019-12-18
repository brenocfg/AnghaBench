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
typedef  int u8 ;
typedef  int u32 ;
typedef  int s8 ;
typedef  float f32 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTL (int,int,int) ; 

void GX_SetIndTexMatrix(u8 indtexmtx,f32 offset_mtx[2][3],s8 scale_exp)
{
	u32 ma,mb;
	u32 val,s,idx;

	if(indtexmtx>0x00 && indtexmtx<0x04) indtexmtx -= 0x01;
	else if(indtexmtx>0x04 && indtexmtx<0x08) indtexmtx -= 0x05;
	else if(indtexmtx>0x08 && indtexmtx<0x0C) indtexmtx -= 0x09;
	else indtexmtx = 0x00;

	s = (scale_exp+17);
	idx = ((indtexmtx<<2)-indtexmtx);

	ma = (u32)(offset_mtx[0][0]*1024.0F);
	mb = (u32)(offset_mtx[1][0]*1024.0F);
	val = (_SHIFTL((0x06+idx),24,8)|_SHIFTL(s,22,2)|_SHIFTL(mb,11,11)|_SHIFTL(ma,0,11));
	GX_LOAD_BP_REG(val);

	ma = (u32)(offset_mtx[0][1]*1024.0F);
	mb = (u32)(offset_mtx[1][1]*1024.0F);
	val = (_SHIFTL((0x07+idx),24,8)|_SHIFTL((s>>2),22,2)|_SHIFTL(mb,11,11)|_SHIFTL(ma,0,11));
	GX_LOAD_BP_REG(val);

	ma = (u32)(offset_mtx[0][2]*1024.0F);
	mb = (u32)(offset_mtx[1][2]*1024.0F);
	val = (_SHIFTL((0x08+idx),24,8)|_SHIFTL((s>>4),22,2)|_SHIFTL(mb,11,11)|_SHIFTL(ma,0,11));
	GX_LOAD_BP_REG(val);
}