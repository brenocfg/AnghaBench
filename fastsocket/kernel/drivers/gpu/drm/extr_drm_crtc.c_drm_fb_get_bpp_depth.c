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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
#define  DRM_FORMAT_ABGR1555 158 
#define  DRM_FORMAT_ABGR2101010 157 
#define  DRM_FORMAT_ABGR8888 156 
#define  DRM_FORMAT_ARGB1555 155 
#define  DRM_FORMAT_ARGB2101010 154 
#define  DRM_FORMAT_ARGB8888 153 
#define  DRM_FORMAT_BGR233 152 
#define  DRM_FORMAT_BGR565 151 
#define  DRM_FORMAT_BGR888 150 
#define  DRM_FORMAT_BGRA1010102 149 
#define  DRM_FORMAT_BGRA5551 148 
#define  DRM_FORMAT_BGRA8888 147 
#define  DRM_FORMAT_BGRX1010102 146 
#define  DRM_FORMAT_BGRX5551 145 
#define  DRM_FORMAT_BGRX8888 144 
#define  DRM_FORMAT_C8 143 
#define  DRM_FORMAT_RGB332 142 
#define  DRM_FORMAT_RGB565 141 
#define  DRM_FORMAT_RGB888 140 
#define  DRM_FORMAT_RGBA1010102 139 
#define  DRM_FORMAT_RGBA5551 138 
#define  DRM_FORMAT_RGBA8888 137 
#define  DRM_FORMAT_RGBX1010102 136 
#define  DRM_FORMAT_RGBX5551 135 
#define  DRM_FORMAT_RGBX8888 134 
#define  DRM_FORMAT_XBGR1555 133 
#define  DRM_FORMAT_XBGR2101010 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB1555 130 
#define  DRM_FORMAT_XRGB2101010 129 
#define  DRM_FORMAT_XRGB8888 128 

void drm_fb_get_bpp_depth(uint32_t format, unsigned int *depth,
			  int *bpp)
{
	switch (format) {
	case DRM_FORMAT_C8:
	case DRM_FORMAT_RGB332:
	case DRM_FORMAT_BGR233:
		*depth = 8;
		*bpp = 8;
		break;
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_XBGR1555:
	case DRM_FORMAT_RGBX5551:
	case DRM_FORMAT_BGRX5551:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_ABGR1555:
	case DRM_FORMAT_RGBA5551:
	case DRM_FORMAT_BGRA5551:
		*depth = 15;
		*bpp = 16;
		break;
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_BGR565:
		*depth = 16;
		*bpp = 16;
		break;
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_BGR888:
		*depth = 24;
		*bpp = 24;
		break;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_BGRX8888:
		*depth = 24;
		*bpp = 32;
		break;
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_XBGR2101010:
	case DRM_FORMAT_RGBX1010102:
	case DRM_FORMAT_BGRX1010102:
	case DRM_FORMAT_ARGB2101010:
	case DRM_FORMAT_ABGR2101010:
	case DRM_FORMAT_RGBA1010102:
	case DRM_FORMAT_BGRA1010102:
		*depth = 30;
		*bpp = 32;
		break;
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_BGRA8888:
		*depth = 32;
		*bpp = 32;
		break;
	default:
		DRM_DEBUG_KMS("unsupported pixel format\n");
		*depth = 0;
		*bpp = 0;
		break;
	}
}