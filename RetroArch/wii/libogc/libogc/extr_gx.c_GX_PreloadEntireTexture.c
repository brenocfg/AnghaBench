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
typedef  scalar_t__ u16 ;
struct __gx_texregion {int tmem_even; int tmem_odd; } ;
struct __gx_texobj {int tex_maddr; int tex_tile_cnt; int tex_tile_type; int tex_size; int tex_flag; int tex_fmt; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  GXTexRegion ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
#define  GX_TF_CI14 137 
#define  GX_TF_CI4 136 
#define  GX_TF_CI8 135 
#define  GX_TF_CMPR 134 
#define  GX_TF_I4 133 
#define  GX_TF_I8 132 
#define  GX_TF_IA4 131 
#define  GX_TF_IA8 130 
#define  GX_TF_RGB565 129 
#define  GX_TF_RGB5A3 128 
 int GX_TF_RGBA8 ; 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int,int,int) ; 
 int /*<<< orphan*/  __GX_FlushTextureState () ; 
 scalar_t__ cntlzw (int) ; 

void GX_PreloadEntireTexture(GXTexObj *obj,GXTexRegion *region)
{
	u32 i,fmt;
	s32 wd,ht;
	u16 cnt = 0;
	u32 regA = 0;
	u32 regB = 0;
	u32 regC = 0;
	u32 regD = 0;
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;
	struct __gx_texregion *reg = (struct __gx_texregion*)region;

	regA = (regA&~0xff000000)|(_SHIFTL(0x60,24,8));
	regA = (regA&~0x00ffffff)|(ptr->tex_maddr&~0xff000000);

	regB = (regB&~0xff000000)|(_SHIFTL(0x61,24,8));
	regB = (regB&~0x00007fff)|(reg->tmem_even&0x00007fff);

	regC = (regC&~0xff000000)|(_SHIFTL(0x62,24,8));
	regC = (regC&~0x00007fff)|(reg->tmem_odd&0x00007fff);

	regD = (regD&~0xff000000)|(_SHIFTL(0x63,24,8));
	regD = (regD&~0x00007fff)|(ptr->tex_tile_cnt&0x00007fff);
	regD = (regD&~0x00018000)|(_SHIFTL(ptr->tex_tile_type,15,2));

	fmt = _SHIFTR(ptr->tex_size,20,4);

	__GX_FlushTextureState();
	GX_LOAD_BP_REG(regA);
	GX_LOAD_BP_REG(regB);
	GX_LOAD_BP_REG(regC);
	GX_LOAD_BP_REG(regD);

	if(ptr->tex_flag&0x01) {
		wd = (ptr->tex_size&0x3ff)+1;
		ht = _SHIFTR(ptr->tex_size,10,10)+1;
		if(wd>ht)
			cnt = (31 - (cntlzw(wd)));
		else
			cnt = (31 - (cntlzw(ht)));
	}

	if(cnt>0) {
		u32 tmem_even,tmem_odd,maddr;
		u32 tile_cnt = ptr->tex_tile_cnt;

		tmem_even = (reg->tmem_even&0xffff);
		tmem_odd = (reg->tmem_odd&0xffff);
		maddr = (ptr->tex_maddr&~0xff000000);

		i = 0;
		while(cnt) {
			u32 w,h;
			u32 te,to;
			u32 xshift,yshift;

			if(fmt==GX_TF_RGBA8) {
				tmem_even += tile_cnt;
				tmem_odd += tile_cnt;
				maddr += (tile_cnt<<1);
			} else {
				maddr += tile_cnt;
				if(i&1) tmem_odd += tile_cnt;
				else tmem_even += tile_cnt;
			}

			te = tmem_even;
			to = tmem_odd;
			if(i&1) {
				te = tmem_odd;
				to = tmem_even;
			}

			w = wd>>(i+1);
			h = wd>>(i+1);
			switch(ptr->tex_fmt) {
				case GX_TF_I4:
				case GX_TF_IA4:
				case GX_TF_CI4:
				case GX_TF_CMPR:
					xshift = 3;
					yshift = 3;
					break;
				case GX_TF_I8:
				case GX_TF_CI8:
					xshift = 3;
					yshift = 2;
					break;
				case GX_TF_IA8:
				case GX_TF_RGB5A3:
				case GX_TF_RGB565:
				case GX_TF_CI14:
					xshift = 2;
					yshift = 2;
					break;
				default:
					xshift = 0;
					yshift = 0;
					break;
			}

			if(!w) w = 1;
			if(!h) h = 1;

			regA = ((regA&~0x00ffffff)|(maddr&0x00ffffff));
			GX_LOAD_BP_REG(regA);

			regB = ((regB&~0x00007fff)|(te&0x00007fff));
			GX_LOAD_BP_REG(regB);

			regC = ((regC&~0x00007fff)|(to&0x00007fff));
			GX_LOAD_BP_REG(regC);

			tile_cnt = (((w+(1<<xshift))-1)>>xshift)*(((h+(1<<yshift))-1)>>yshift);
			regD = ((regD&~0x00007fff)|(tile_cnt&0x00007fff));
			GX_LOAD_BP_REG(regD);

			++i;
			--cnt;
		}
	}
	__GX_FlushTextureState();
}