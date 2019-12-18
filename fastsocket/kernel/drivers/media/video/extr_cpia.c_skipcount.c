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

/* Variables and functions */
#define  VIDEO_PALETTE_GREY 135 
#define  VIDEO_PALETTE_RGB24 134 
#define  VIDEO_PALETTE_RGB32 133 
#define  VIDEO_PALETTE_RGB555 132 
#define  VIDEO_PALETTE_RGB565 131 
#define  VIDEO_PALETTE_UYVY 130 
#define  VIDEO_PALETTE_YUV422 129 
#define  VIDEO_PALETTE_YUYV 128 

__attribute__((used)) static int skipcount(int count, int fmt)
{
	switch(fmt) {
	case VIDEO_PALETTE_GREY:
		return count;
	case VIDEO_PALETTE_RGB555:
	case VIDEO_PALETTE_RGB565:
	case VIDEO_PALETTE_YUV422:
	case VIDEO_PALETTE_YUYV:
	case VIDEO_PALETTE_UYVY:
		return 2*count;
	case VIDEO_PALETTE_RGB24:
		return 3*count;
	case VIDEO_PALETTE_RGB32:
		return 4*count;
	default:
		return 0;
	}
}