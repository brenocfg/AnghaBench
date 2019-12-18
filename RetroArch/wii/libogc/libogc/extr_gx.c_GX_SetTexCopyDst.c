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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int texCopyDst; int texCopyCntrl; int texCopyZTex; } ;

/* Variables and functions */
 int GX_CTF_YUVA8 ; 
 int GX_TF_I4 ; 
 int GX_TF_RGB565 ; 
 int GX_TF_Z16 ; 
 int _GX_TF_ZTF ; 
 int _SHIFTL (int,int,int) ; 
 int /*<<< orphan*/  __GetImageTileCount (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 TYPE_1__* __gx ; 

void GX_SetTexCopyDst(u16 wd,u16 ht,u32 fmt,u8 mipmap)
{
	u8 lfmt = fmt&0xf;
	u32 xtiles,ytiles,zplanes;

	__GetImageTileCount(fmt,wd,ht,&xtiles,&ytiles,&zplanes);
	__gx->texCopyDst = (__gx->texCopyDst&~0x3ff)|((xtiles*zplanes)&0x3ff);

	if(fmt==GX_TF_Z16) lfmt = 11;
	if(fmt==GX_CTF_YUVA8 || (fmt>=GX_TF_I4 && fmt<GX_TF_RGB565)) __gx->texCopyCntrl = (__gx->texCopyCntrl&~0x18000)|0x18000;
	else __gx->texCopyCntrl = (__gx->texCopyCntrl&~0x18000)|0x10000;

	__gx->texCopyCntrl = (__gx->texCopyCntrl&~0x8)|(lfmt&0x8);
	__gx->texCopyCntrl = (__gx->texCopyCntrl&~0x200)|(_SHIFTL(mipmap,9,1));
	__gx->texCopyCntrl = (__gx->texCopyCntrl&~0x70)|(_SHIFTL(lfmt,4,3));

	__gx->texCopyDst = (__gx->texCopyDst&~0xff000000)|(_SHIFTL(0x4d,24,8));

	__gx->texCopyZTex = ((fmt&_GX_TF_ZTF)==_GX_TF_ZTF);
}