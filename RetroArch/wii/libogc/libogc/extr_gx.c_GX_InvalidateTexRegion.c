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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct __gx_texregion {int tmem_even; int tmem_odd; scalar_t__ ismipmap; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  GXTexRegion ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 scalar_t__ _SHIFTL (int,int,int) ; 
 scalar_t__ _SHIFTR (int,int,int) ; 
 int /*<<< orphan*/  __GX_FlushTextureState () ; 

void GX_InvalidateTexRegion(GXTexRegion *region)
{
	u8 ismipmap;
	s32 cw_e,ch_e,cw_o,ch_o;
	u32 size,tmp,regvalA = 0,regvalB = 0;
	struct __gx_texregion *ptr = (struct __gx_texregion*)region;

	cw_e = (_SHIFTR(ptr->tmem_even,15,3))-1;
	ch_e = (_SHIFTR(ptr->tmem_even,18,3))-1;

	cw_o = (_SHIFTR(ptr->tmem_odd,15,3))-1;
	ch_o = (_SHIFTR(ptr->tmem_odd,18,3))-1;

	if(cw_e<0) cw_e = 0;
	if(ch_e<0) ch_e = 0;
	if(cw_o<0) cw_o = 0;
	if(ch_o<0) ch_o = 0;

	ismipmap = ptr->ismipmap;

	tmp = size = cw_e+ch_e;
	if(ismipmap) size = (tmp+cw_o+ch_o)-2;
	regvalA = _SHIFTR((ptr->tmem_even&0x7fff),6,9)|(_SHIFTL(size,9,4))|(_SHIFTL(0x66,24,8));

	if(cw_o!=0) {
		size = cw_o+ch_o;
		if(ismipmap) size += (tmp-2);
		regvalB = _SHIFTR((ptr->tmem_odd&0x7fff),6,9)|(_SHIFTL(size,9,4))|(_SHIFTL(0x66,24,8));
	}
	__GX_FlushTextureState();
	GX_LOAD_BP_REG(regvalA);
	if(cw_o!=0) GX_LOAD_BP_REG(regvalB);
	__GX_FlushTextureState();
}