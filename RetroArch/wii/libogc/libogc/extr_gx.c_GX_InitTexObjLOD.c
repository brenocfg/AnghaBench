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
struct __gx_texobj {int tex_filt; int tex_lod; } ;
typedef  float f32 ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int GX_LINEAR ; 
 int _SHIFTL (int,int,int) ; 

void GX_InitTexObjLOD(GXTexObj *obj,u8 minfilt,u8 magfilt,f32 minlod,f32 maxlod,f32 lodbias,u8 biasclamp,u8 edgelod,u8 maxaniso)
{
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;
	static u8 GX2HWFiltConv[] = {0x00,0x04,0x01,0x05,0x02,0x06,0x00,0x00};
	//static u8 HW2GXFiltConv[] = {0x00,0x02,0x04,0x00,0x01,0x03,0x05,0x00};

	if(lodbias<-4.0f) lodbias = -4.0f;
	else if(lodbias==4.0f) lodbias = 3.99f;

	ptr->tex_filt = (ptr->tex_filt&~0x1fe00)|(_SHIFTL(((u32)(32.0f*lodbias)),9,8));
	ptr->tex_filt = (ptr->tex_filt&~0x10)|(_SHIFTL((magfilt==GX_LINEAR?1:0),4,1));
	ptr->tex_filt = (ptr->tex_filt&~0xe0)|(_SHIFTL(GX2HWFiltConv[minfilt],5,3));
	ptr->tex_filt = (ptr->tex_filt&~0x100)|(_SHIFTL(!(edgelod&0xff),8,1));
	ptr->tex_filt = (ptr->tex_filt&~0x180000)|(_SHIFTL(maxaniso,19,2));
	ptr->tex_filt = (ptr->tex_filt&~0x200000)|(_SHIFTL(biasclamp,21,1));

	if(minlod<0.0f) minlod = 0.0f;
	else if(minlod>10.0f) minlod = 10.0f;

	if(maxlod<0.0f) maxlod = 0.0f;
	else if(maxlod>10.0f) maxlod = 10.0f;

	ptr->tex_lod = (ptr->tex_lod&~0xff)|(((u32)(16.0f*minlod))&0xff);
	ptr->tex_lod = (ptr->tex_lod&~0xff00)|(_SHIFTL(((u32)(16.0f*maxlod)),8,8));
}