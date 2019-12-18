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
struct TYPE_2__ {int vcdLo; int vcdNrms; int vcdHi; } ;

/* Variables and functions */
#define  GX_VA_CLR0 149 
#define  GX_VA_CLR1 148 
#define  GX_VA_NBT 147 
#define  GX_VA_NRM 146 
#define  GX_VA_POS 145 
#define  GX_VA_PTNMTXIDX 144 
#define  GX_VA_TEX0 143 
#define  GX_VA_TEX0MTXIDX 142 
#define  GX_VA_TEX1 141 
#define  GX_VA_TEX1MTXIDX 140 
#define  GX_VA_TEX2 139 
#define  GX_VA_TEX2MTXIDX 138 
#define  GX_VA_TEX3 137 
#define  GX_VA_TEX3MTXIDX 136 
#define  GX_VA_TEX4 135 
#define  GX_VA_TEX4MTXIDX 134 
#define  GX_VA_TEX5 133 
#define  GX_VA_TEX5MTXIDX 132 
#define  GX_VA_TEX6 131 
#define  GX_VA_TEX6MTXIDX 130 
#define  GX_VA_TEX7 129 
#define  GX_VA_TEX7MTXIDX 128 
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* __gx ; 

__attribute__((used)) static __inline__ void __SETVCDATTR(u8 attr,u8 type)
{
	switch(attr) {
		case GX_VA_PTNMTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x1)|(type&0x1);
			break;
		case GX_VA_TEX0MTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x2)|(_SHIFTL(type,1,1));
			break;
		case GX_VA_TEX1MTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x4)|(_SHIFTL(type,2,1));
			break;
		case GX_VA_TEX2MTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x8)|(_SHIFTL(type,3,1));
			break;
		case GX_VA_TEX3MTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x10)|(_SHIFTL(type,4,1));
			break;
		case GX_VA_TEX4MTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x20)|(_SHIFTL(type,5,1));
			break;
		case GX_VA_TEX5MTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x40)|(_SHIFTL(type,6,1));
			break;
		case GX_VA_TEX6MTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x80)|(_SHIFTL(type,7,1));
			break;
		case GX_VA_TEX7MTXIDX:
			__gx->vcdLo = (__gx->vcdLo&~0x100)|(_SHIFTL(type,8,1));
			break;
		case GX_VA_POS:
			__gx->vcdLo = (__gx->vcdLo&~0x600)|(_SHIFTL(type,9,2));
			break;
		case GX_VA_NRM:
			__gx->vcdLo = (__gx->vcdLo&~0x1800)|(_SHIFTL(type,11,2));
			__gx->vcdNrms = 1;
			break;
		case GX_VA_NBT:
			__gx->vcdLo = (__gx->vcdLo&~0x1800)|(_SHIFTL(type,11,2));
			__gx->vcdNrms = 2;
			break;
		case GX_VA_CLR0:
			__gx->vcdLo = (__gx->vcdLo&~0x6000)|(_SHIFTL(type,13,2));
			break;
		case GX_VA_CLR1:
			__gx->vcdLo = (__gx->vcdLo&~0x18000)|(_SHIFTL(type,15,2));
			break;
		case GX_VA_TEX0:
			__gx->vcdHi = (__gx->vcdHi&~0x3)|(type&0x3);
			break;
		case GX_VA_TEX1:
			__gx->vcdHi = (__gx->vcdHi&~0xc)|(_SHIFTL(type,2,2));
			break;
		case GX_VA_TEX2:
			__gx->vcdHi = (__gx->vcdHi&~0x30)|(_SHIFTL(type,4,2));
			break;
		case GX_VA_TEX3:
			__gx->vcdHi = (__gx->vcdHi&~0xc0)|(_SHIFTL(type,6,2));
			break;
		case GX_VA_TEX4:
			__gx->vcdHi = (__gx->vcdHi&~0x300)|(_SHIFTL(type,8,2));
			break;
		case GX_VA_TEX5:
			__gx->vcdHi = (__gx->vcdHi&~0xc00)|(_SHIFTL(type,10,2));
			break;
		case GX_VA_TEX6:
			__gx->vcdHi = (__gx->vcdHi&~0x3000)|(_SHIFTL(type,12,2));
			break;
		case GX_VA_TEX7:
			__gx->vcdHi = (__gx->vcdHi&~0xc000)|(_SHIFTL(type,14,2));
			break;
	}
}