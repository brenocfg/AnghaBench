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
typedef  int u16 ;

/* Variables and functions */
#define  GX_CTF_A8 150 
#define  GX_CTF_B8 149 
#define  GX_CTF_G8 148 
#define  GX_CTF_GB8 147 
#define  GX_CTF_R4 146 
#define  GX_CTF_R8 145 
#define  GX_CTF_RA4 144 
#define  GX_CTF_RA8 143 
#define  GX_CTF_RG8 142 
#define  GX_CTF_Z16L 141 
#define  GX_CTF_Z4 140 
#define  GX_CTF_Z8L 139 
#define  GX_CTF_Z8M 138 
#define  GX_TF_I4 137 
#define  GX_TF_I8 136 
#define  GX_TF_IA4 135 
#define  GX_TF_IA8 134 
#define  GX_TF_RGB565 133 
#define  GX_TF_RGB5A3 132 
#define  GX_TF_RGBA8 131 
#define  GX_TF_Z16 130 
#define  GX_TF_Z24X8 129 
#define  GX_TF_Z8 128 

__attribute__((used)) static void __GetImageTileCount(u32 fmt,u16 wd,u16 ht,u32 *xtiles,u32 *ytiles,u32 *zplanes)
{
	u32 xshift,yshift,tile;

	switch(fmt) {
		case GX_TF_I4:
		case GX_TF_IA4:
		case GX_CTF_R4:
		case GX_CTF_RA4:
		case GX_CTF_Z4:
			xshift = 3;
			yshift = 3;
			break;
		case GX_TF_Z8:
		case GX_TF_I8:
		case GX_CTF_A8:
		case GX_CTF_R8:
		case GX_CTF_G8:
		case GX_CTF_B8:
		case GX_CTF_Z8M:
		case GX_CTF_Z8L:
			xshift = 3;
			yshift = 2;
			break;
		case GX_TF_IA8:
		case GX_CTF_RA8:
		case GX_CTF_RG8:
		case GX_CTF_GB8:
		case GX_TF_Z16:
		case GX_TF_Z24X8:
		case GX_CTF_Z16L:
		case GX_TF_RGB565:
		case GX_TF_RGB5A3:
		case GX_TF_RGBA8:
			xshift = 2;
			yshift = 2;
			break;
		default:
			xshift = 0;
			yshift = 0;
			break;
	}

	if(!(wd&0xffff)) wd = 1;
	if(!(ht&0xffff)) ht = 1;

	wd &= 0xffff;
	tile = (wd+((1<<xshift)-1))>>xshift;
	*xtiles = tile;

	ht &= 0xffff;
	tile = (ht+((1<<yshift)-1))>>yshift;
	*ytiles = tile;

	*zplanes = 1;
	if(fmt==GX_TF_RGBA8 || fmt==GX_TF_Z24X8) *zplanes = 2;
}