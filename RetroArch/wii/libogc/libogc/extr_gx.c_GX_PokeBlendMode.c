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
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ GX_BM_BLEND ; 
 scalar_t__ GX_BM_LOGIC ; 
 scalar_t__ GX_BM_SUBTRACT ; 
 int _SHIFTL (scalar_t__,int,int) ; 
 int* _peReg ; 

void GX_PokeBlendMode(u8 type,u8 src_fact,u8 dst_fact,u8 op)
{
	u32 regval = _peReg[1];

	regval = (regval&~0x1);
	if(type==GX_BM_BLEND || type==GX_BM_SUBTRACT) regval |= 0x1;

	regval = (regval&~0x800);
	if(type==GX_BM_SUBTRACT) regval |= 0x800;

	regval = (regval&~0x2);
	if(type==GX_BM_LOGIC) regval |= 0x2;

	regval = (regval&~0xF000)|(_SHIFTL(op,12,4));
	regval = (regval&~0xE0)|(_SHIFTL(dst_fact,5,3));
	regval = (regval&~0x700)|(_SHIFTL(src_fact,8,3));

	regval |= 0x41000000;
	_peReg[1] = (u16)regval;
}