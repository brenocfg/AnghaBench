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
struct __gx_texobj {int tex_filt; int tex_flag; int tex_fmt; int tex_size; int tex_maddr; int tex_tile_type; int tex_tile_cnt; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
#define  GX_TF_CI14 138 
#define  GX_TF_CI4 137 
#define  GX_TF_CI8 136 
#define  GX_TF_CMPR 135 
#define  GX_TF_I4 134 
#define  GX_TF_I8 133 
#define  GX_TF_IA4 132 
#define  GX_TF_IA8 131 
#define  GX_TF_RGB565 130 
#define  GX_TF_RGB5A3 129 
#define  GX_TF_RGBA8 128 
 int /*<<< orphan*/  MEM_VIRTUAL_TO_PHYSICAL (void*) ; 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void GX_InitTexObj(GXTexObj *obj,void *img_ptr,u16 wd,u16 ht,u8 fmt,u8 wrap_s,u8 wrap_t,u8 mipmap)
{
	u32 nwd,nht;
	u32 xshift,yshift;
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;

	if(!obj) return;

	memset(obj,0,sizeof(GXTexObj));

	ptr->tex_filt = (ptr->tex_filt&~0x03)|(wrap_s&3);
	ptr->tex_filt = (ptr->tex_filt&~0x0c)|(_SHIFTL(wrap_t,2,2));
	ptr->tex_filt = (ptr->tex_filt&~0x10)|0x10;

	if(mipmap) {
		ptr->tex_flag |= 0x01;
		if(fmt==GX_TF_CI4 || fmt==GX_TF_CI8 || fmt==GX_TF_CI14)
			ptr->tex_filt = (ptr->tex_filt&~0xe0)|0x00a0;
		else
			ptr->tex_filt = (ptr->tex_filt&~0xe0)|0x00c0;
	} else
		ptr->tex_filt= (ptr->tex_filt&~0xE0)|0x0080;

	ptr->tex_fmt = fmt;
	ptr->tex_size = (ptr->tex_size&~0x3ff)|((wd-1)&0x3ff);
	ptr->tex_size = (ptr->tex_size&~0xFFC00)|(_SHIFTL((ht-1),10,10));
	ptr->tex_size = (ptr->tex_size&~0xF00000)|(_SHIFTL(fmt,20,4));
	ptr->tex_maddr = (ptr->tex_maddr&~0x00ffffff)|(_SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(img_ptr),5,24));

	switch(fmt) {
		case GX_TF_I4:
		case GX_TF_CI4:
			xshift = 3;
			yshift = 3;
			ptr->tex_tile_type = 1;
			break;
		case GX_TF_I8:
		case GX_TF_IA4:
		case GX_TF_CI8:
			xshift = 3;
			yshift = 2;
			ptr->tex_tile_type = 2;
			break;
		case GX_TF_IA8:
		case GX_TF_RGB565:
		case GX_TF_RGB5A3:
		case GX_TF_RGBA8:
			xshift = 2;
			yshift = 2;
			ptr->tex_tile_type = 2;
			break;
		case GX_TF_CI14:
			xshift = 2;
			yshift = 2;
			ptr->tex_tile_type = 3;
			break;
		case GX_TF_CMPR:
			xshift = 3;
			yshift = 3;
			ptr->tex_tile_type = 0;
			break;
		default:
			xshift = 2;
			yshift = 2;
			ptr->tex_tile_type = 2;
			break;
	}

	nwd = ((wd+(1<<xshift))-1)>>xshift;
	nht = ((ht+(1<<yshift))-1)>>yshift;
	ptr->tex_tile_cnt = (nwd*nht)&0x7fff;

	ptr->tex_flag |= 0x0002;
}