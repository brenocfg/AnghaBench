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
struct TYPE_2__ {int* tevTexMap; int tevTexCoordEnable; int* tevRasOrder; int dirtyState; } ;

/* Variables and functions */
 int GX_ALPHA_BUMP ; 
 int GX_COLORNULL ; 
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int GX_MAXCOORD ; 
 int GX_MAX_TEXMAP ; 
 int GX_TEXMAP_NULL ; 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int,int,int) ; 
 TYPE_1__* __gx ; 
 int* _gxtevcolid ; 

void GX_SetTevOrder(u8 tevstage,u8 texcoord,u32 texmap,u8 color)
{
	u8 colid;
	u32 texm,texc,tmp;
	u32 reg = 3+(_SHIFTR(tevstage,1,3));

	__gx->tevTexMap[(tevstage&0xf)] = texmap;

	texm = (texmap&~0x100);
	if(texm>=GX_MAX_TEXMAP) texm = 0;
	if(texcoord>=GX_MAXCOORD) {
		texc = 0;
		__gx->tevTexCoordEnable &= ~(_SHIFTL(1,tevstage,1));
	} else {
		texc = texcoord;
		__gx->tevTexCoordEnable |= (_SHIFTL(1,tevstage,1));
	}

	if(tevstage&1) {
		__gx->tevRasOrder[reg] = (__gx->tevRasOrder[reg]&~0x7000)|(_SHIFTL(texm,12,3));
		__gx->tevRasOrder[reg] = (__gx->tevRasOrder[reg]&~0x38000)|(_SHIFTL(texc,15,3));

		colid = GX_ALPHA_BUMP;
		if(color!=GX_COLORNULL) colid = _gxtevcolid[color];
		__gx->tevRasOrder[reg] = (__gx->tevRasOrder[reg]&~0x380000)|(_SHIFTL(colid,19,3));

		tmp = 1;
		if(texmap==GX_TEXMAP_NULL || texmap&0x100) tmp = 0;
		__gx->tevRasOrder[reg] = (__gx->tevRasOrder[reg]&~0x40000)|(_SHIFTL(tmp,18,1));
	} else {
		__gx->tevRasOrder[reg] = (__gx->tevRasOrder[reg]&~0x7)|(texm&0x7);
		__gx->tevRasOrder[reg] = (__gx->tevRasOrder[reg]&~0x38)|(_SHIFTL(texc,3,3));

		colid = GX_ALPHA_BUMP;
		if(color!=GX_COLORNULL) colid = _gxtevcolid[color];
		__gx->tevRasOrder[reg] = (__gx->tevRasOrder[reg]&~0x380)|(_SHIFTL(colid,7,3));

		tmp = 1;
		if(texmap==GX_TEXMAP_NULL || texmap&0x100) tmp = 0;
		__gx->tevRasOrder[reg] = (__gx->tevRasOrder[reg]&~0x40)|(_SHIFTL(tmp,6,1));
	}
	GX_LOAD_BP_REG(__gx->tevRasOrder[reg]);
	__gx->dirtyState |= 0x0001;
}