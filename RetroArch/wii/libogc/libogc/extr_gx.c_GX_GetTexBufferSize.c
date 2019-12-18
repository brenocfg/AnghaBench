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
typedef  int u16 ;

/* Variables and functions */
#define  GX_CTF_A8 151 
#define  GX_CTF_B8 150 
#define  GX_CTF_G8 149 
#define  GX_CTF_GB8 148 
#define  GX_CTF_R4 147 
#define  GX_CTF_R8 146 
#define  GX_CTF_RA4 145 
#define  GX_CTF_RA8 144 
#define  GX_CTF_RG8 143 
#define  GX_CTF_Z16L 142 
#define  GX_CTF_Z4 141 
#define  GX_CTF_Z8L 140 
#define  GX_CTF_Z8M 139 
#define  GX_TF_CMPR 138 
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

u32 GX_GetTexBufferSize(u16 wd,u16 ht,u32 fmt,u8 mipmap,u8 maxlod)
{
	u32 xshift,yshift,xtiles,ytiles,bitsize,size;

	switch(fmt) {
		case GX_TF_I4:
		case GX_TF_CMPR:
		case GX_CTF_R4:
		case GX_CTF_RA4:
		case GX_CTF_Z4:
			xshift = 3;
			yshift = 3;
			break;
		case GX_TF_Z8:
		case GX_TF_I8:
		case GX_TF_IA4:
		case GX_CTF_A8:
		case GX_CTF_R8:
		case GX_CTF_G8:
		case GX_CTF_B8:
		case GX_CTF_RG8:
		case GX_CTF_GB8:
		case GX_CTF_Z8M:
		case GX_CTF_Z8L:
			xshift = 3;
			yshift = 2;
			break;
		case GX_TF_IA8:
		case GX_TF_Z16:
		case GX_TF_Z24X8:
		case GX_TF_RGB565:
		case GX_TF_RGB5A3:
		case GX_TF_RGBA8:
		case GX_CTF_Z16L:
		case GX_CTF_RA8:
			xshift = 2;
			yshift = 2;
			break;
		default:
			xshift = 2;
			yshift = 2;
			break;
	}

	bitsize = 32;
	if(fmt==GX_TF_RGBA8 || fmt==GX_TF_Z24X8) bitsize = 64;

	size = 0;
	if(mipmap) {
		u32 cnt = (maxlod&0xff);
		while(cnt) {
			u32 w = wd&0xffff;
			u32 h = ht&0xffff;
			xtiles = ((w+(1<<xshift))-1)>>xshift;
			ytiles = ((h+(1<<yshift))-1)>>yshift;
			if(cnt==0) return size;

			size += ((xtiles*ytiles)*bitsize);
			if(w==0x0001 && h==0x0001) return size;
			if(wd>0x0001) wd = (w>>1);
			else wd = 0x0001;
			if(ht>0x0001) ht = (h>>1);
			else ht = 0x0001;

			--cnt;
		}
		return size;
	}

	wd &= 0xffff;
	xtiles = (wd+((1<<xshift)-1))>>xshift;

	ht &= 0xffff;
	ytiles = (ht+((1<<yshift)-1))>>yshift;

	size = ((xtiles*ytiles)*bitsize);

	return size;
}