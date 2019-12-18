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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int* texCoordGen; int* texCoordGen2; int mtxIdxLo; int mtxIdxHi; int dirtyState; } ;

/* Variables and functions */
 scalar_t__ GX_DTTMTX0 ; 
 int GX_MAXCOORD ; 
#define  GX_TEXCOORD0 149 
#define  GX_TEXCOORD1 148 
#define  GX_TEXCOORD2 147 
#define  GX_TEXCOORD3 146 
#define  GX_TEXCOORD4 145 
#define  GX_TEXCOORD5 144 
#define  GX_TEXCOORD6 143 
#define  GX_TEXCOORD7 142 
#define  GX_TG_BINRM 141 
 int GX_TG_BUMP0 ; 
 int GX_TG_BUMP7 ; 
#define  GX_TG_COLOR0 140 
#define  GX_TG_COLOR1 139 
 int GX_TG_MTX2x4 ; 
 int GX_TG_MTX3x4 ; 
#define  GX_TG_NRM 138 
#define  GX_TG_POS 137 
 int GX_TG_SRTG ; 
#define  GX_TG_TANGENT 136 
#define  GX_TG_TEX0 135 
#define  GX_TG_TEX1 134 
#define  GX_TG_TEX2 133 
#define  GX_TG_TEX3 132 
#define  GX_TG_TEX4 131 
#define  GX_TG_TEX5 130 
#define  GX_TG_TEX6 129 
#define  GX_TG_TEX7 128 
 scalar_t__ GX_TG_TEXCOORD0 ; 
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetTexCoordGen2(u16 texcoord,u32 tgen_typ,u32 tgen_src,u32 mtxsrc,u32 normalize,u32 postmtx)
{
	u32 txc;
	u32 texcoords;
	u8 vtxrow,stq;

	if(texcoord>=GX_MAXCOORD) return;

	stq = 0;
	switch(tgen_src) {
		case GX_TG_POS:
			vtxrow = 0;
			stq = 1;
			break;
		case GX_TG_NRM:
			vtxrow = 1;
			stq = 1;
			break;
		case GX_TG_BINRM:
			vtxrow = 3;
			stq = 1;
			break;
		case GX_TG_TANGENT:
			vtxrow = 4;
			stq = 1;
			break;
		case GX_TG_COLOR0:
			vtxrow = 2;
			break;
		case GX_TG_COLOR1:
			vtxrow = 2;
			break;
		case GX_TG_TEX0:
			vtxrow = 5;
			break;
		case GX_TG_TEX1:
			vtxrow = 6;
			break;
		case GX_TG_TEX2:
			vtxrow = 7;
			break;
		case GX_TG_TEX3:
			vtxrow = 8;
			break;
		case GX_TG_TEX4:
			vtxrow = 9;
			break;
		case GX_TG_TEX5:
			vtxrow = 10;
			break;
		case GX_TG_TEX6:
			vtxrow = 11;
			break;
		case GX_TG_TEX7:
			vtxrow = 12;
			break;
		default:
			vtxrow = 5;
			break;
	}

	texcoords = 0;
	txc = (texcoord&7);
	if((tgen_typ==GX_TG_MTX3x4 || tgen_typ==GX_TG_MTX2x4))
	{
		if(tgen_typ==GX_TG_MTX3x4) texcoords = 0x02;

		texcoords |= (_SHIFTL(stq,2,1));
		texcoords |= (_SHIFTL(vtxrow,7,5));
	} else if((tgen_typ>=GX_TG_BUMP0 && tgen_typ<=GX_TG_BUMP7))
	{
		tgen_src -= GX_TG_TEXCOORD0;
		tgen_typ -= GX_TG_BUMP0;

		texcoords = 0x10;
		texcoords |= (_SHIFTL(stq,2,1));
		texcoords |= (_SHIFTL(vtxrow,7,5));
		texcoords |= (_SHIFTL(tgen_src,12,3));
		texcoords |= (_SHIFTL(tgen_typ,15,3));
	} else if(tgen_typ==GX_TG_SRTG) {
		if(tgen_src==GX_TG_COLOR0) texcoords = 0x20;
		else if(tgen_src==GX_TG_COLOR1) texcoords = 0x30;
		texcoords |= (_SHIFTL(stq,2,1));
		texcoords |= (_SHIFTL(2,7,5));
	}

	postmtx -= GX_DTTMTX0;
	__gx->texCoordGen[txc] = texcoords;
	__gx->texCoordGen2[txc] = ((_SHIFTL(normalize,8,1))|(postmtx&0x3f));

	switch(texcoord) {
		case GX_TEXCOORD0:
			__gx->mtxIdxLo = (__gx->mtxIdxLo&~0xfc0)|(_SHIFTL(mtxsrc,6,6));
			break;
		case GX_TEXCOORD1:
			__gx->mtxIdxLo = (__gx->mtxIdxLo&~0x3f000)|(_SHIFTL(mtxsrc,12,6));
			break;
		case GX_TEXCOORD2:
			__gx->mtxIdxLo = (__gx->mtxIdxLo&~0xfc0000)|(_SHIFTL(mtxsrc,18,6));
			break;
		case GX_TEXCOORD3:
			__gx->mtxIdxLo = (__gx->mtxIdxLo&~0x3f000000)|(_SHIFTL(mtxsrc,24,6));
			break;
		case GX_TEXCOORD4:
			__gx->mtxIdxHi = (__gx->mtxIdxHi&~0x3f)|(mtxsrc&0x3f);
			break;
		case GX_TEXCOORD5:
			__gx->mtxIdxHi = (__gx->mtxIdxHi&~0xfc0)|(_SHIFTL(mtxsrc,6,6));
			break;
		case GX_TEXCOORD6:
			__gx->mtxIdxHi = (__gx->mtxIdxHi&~0x3f000)|(_SHIFTL(mtxsrc,12,6));
			break;
		case GX_TEXCOORD7:
			__gx->mtxIdxHi = (__gx->mtxIdxHi&~0xfc0000)|(_SHIFTL(mtxsrc,18,6));
			break;
	}
	__gx->dirtyState |= (0x04000000|(0x00010000<<texcoord));
}