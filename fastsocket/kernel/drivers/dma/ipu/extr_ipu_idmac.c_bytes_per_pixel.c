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
typedef  enum pixel_fmt { ____Placeholder_pixel_fmt } pixel_fmt ;

/* Variables and functions */
#define  IPU_PIX_FMT_ABGR32 140 
#define  IPU_PIX_FMT_BGR24 139 
#define  IPU_PIX_FMT_BGR32 138 
#define  IPU_PIX_FMT_GENERIC 137 
#define  IPU_PIX_FMT_GENERIC_32 136 
#define  IPU_PIX_FMT_RGB24 135 
#define  IPU_PIX_FMT_RGB32 134 
#define  IPU_PIX_FMT_RGB332 133 
#define  IPU_PIX_FMT_RGB565 132 
#define  IPU_PIX_FMT_UYVY 131 
#define  IPU_PIX_FMT_YUV420P 130 
#define  IPU_PIX_FMT_YUV422P 129 
#define  IPU_PIX_FMT_YUYV 128 

__attribute__((used)) static uint32_t bytes_per_pixel(enum pixel_fmt fmt)
{
	switch (fmt) {
	case IPU_PIX_FMT_GENERIC:	/* generic data */
	case IPU_PIX_FMT_RGB332:
	case IPU_PIX_FMT_YUV420P:
	case IPU_PIX_FMT_YUV422P:
	default:
		return 1;
	case IPU_PIX_FMT_RGB565:
	case IPU_PIX_FMT_YUYV:
	case IPU_PIX_FMT_UYVY:
		return 2;
	case IPU_PIX_FMT_BGR24:
	case IPU_PIX_FMT_RGB24:
		return 3;
	case IPU_PIX_FMT_GENERIC_32:	/* generic data */
	case IPU_PIX_FMT_BGR32:
	case IPU_PIX_FMT_RGB32:
	case IPU_PIX_FMT_ABGR32:
		return 4;
	}
}