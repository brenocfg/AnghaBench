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
typedef  int SceGxmTextureFormat ;

/* Variables and functions */
#define  SCE_GXM_TEXTURE_BASE_FORMAT_F32 144 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_P8 143 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_S32 142 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_S5S5U6 141 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_S8 140 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_S8S8 139 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8 138 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 137 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 136 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U32 135 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 134 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U5U6U5 133 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U8 132 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U8U3U3U2 131 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U8U8 130 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8 129 
#define  SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 128 

__attribute__((used)) static int tex_format_to_bytespp(SceGxmTextureFormat format)
{
	switch (format & 0x9f000000U) {
	case SCE_GXM_TEXTURE_BASE_FORMAT_U8:
	case SCE_GXM_TEXTURE_BASE_FORMAT_S8:
	case SCE_GXM_TEXTURE_BASE_FORMAT_P8:
		return 1;
	case SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4:
	case SCE_GXM_TEXTURE_BASE_FORMAT_U8U3U3U2:
	case SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5:
	case SCE_GXM_TEXTURE_BASE_FORMAT_U5U6U5:
	case SCE_GXM_TEXTURE_BASE_FORMAT_S5S5U6:
	case SCE_GXM_TEXTURE_BASE_FORMAT_U8U8:
	case SCE_GXM_TEXTURE_BASE_FORMAT_S8S8:
		return 2;
	case SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8:
	case SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8:
		return 3;
	case SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8:
	case SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8:
	case SCE_GXM_TEXTURE_BASE_FORMAT_F32:
	case SCE_GXM_TEXTURE_BASE_FORMAT_U32:
	case SCE_GXM_TEXTURE_BASE_FORMAT_S32:
	default:
		return 4;
	}
}