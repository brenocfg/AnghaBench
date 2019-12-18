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

__attribute__((used)) static u32 TPL_GetTextureSize(u32 width,u32 height,u32 fmt)
{
	u32 size = 0;

	switch(fmt) {
			case GX_TF_I4:
			case GX_TF_CI4:
			case GX_TF_CMPR:
				size = ((width+7)>>3)*((height+7)>>3)*32;
				break;
			case GX_TF_I8:
			case GX_TF_IA4:
			case GX_TF_CI8:
				size = ((width+7)>>3)*((height+7)>>2)*32;
				break;
			case GX_TF_IA8:
			case GX_TF_CI14:
			case GX_TF_RGB565:
			case GX_TF_RGB5A3:
				size = ((width+3)>>2)*((height+3)>>2)*32;
				break;
			case GX_TF_RGBA8:
				size = ((width+3)>>2)*((height+3)>>2)*32*2;
				break;
			default:
				break;
	}
	return size;
}