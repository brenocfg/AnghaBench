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
 int /*<<< orphan*/  DBG (char*,int) ; 
 int LIMIT (int) ; 
#define  VIDEO_PALETTE_GREY 135 
#define  VIDEO_PALETTE_RGB24 134 
#define  VIDEO_PALETTE_RGB32 133 
#define  VIDEO_PALETTE_RGB555 132 
#define  VIDEO_PALETTE_RGB565 131 
#define  VIDEO_PALETTE_UYVY 130 
#define  VIDEO_PALETTE_YUV422 129 
#define  VIDEO_PALETTE_YUYV 128 

__attribute__((used)) static int yuvconvert(unsigned char *yuv, unsigned char *rgb, int out_fmt,
		      int in_uyvy, int mmap_kludge)
{
	int y, u, v, r, g, b, y1;

	switch(out_fmt) {
	case VIDEO_PALETTE_RGB555:
	case VIDEO_PALETTE_RGB565:
	case VIDEO_PALETTE_RGB24:
	case VIDEO_PALETTE_RGB32:
		if (in_uyvy) {
			u = *yuv++ - 128;
			y = (*yuv++ - 16) * 76310;
			v = *yuv++ - 128;
			y1 = (*yuv - 16) * 76310;
		} else {
			y = (*yuv++ - 16) * 76310;
			u = *yuv++ - 128;
			y1 = (*yuv++ - 16) * 76310;
			v = *yuv - 128;
		}
		r = 104635 * v;
		g = -25690 * u + -53294 * v;
		b = 132278 * u;
		break;
	default:
		y = *yuv++;
		u = *yuv++;
		y1 = *yuv++;
		v = *yuv;
		/* Just to avoid compiler warnings */
		r = 0;
		g = 0;
		b = 0;
		break;
	}
	switch(out_fmt) {
	case VIDEO_PALETTE_RGB555:
		*rgb++ = ((LIMIT(g+y) & 0xf8) << 2) | (LIMIT(b+y) >> 3);
		*rgb++ = ((LIMIT(r+y) & 0xf8) >> 1) | (LIMIT(g+y) >> 6);
		*rgb++ = ((LIMIT(g+y1) & 0xf8) << 2) | (LIMIT(b+y1) >> 3);
		*rgb = ((LIMIT(r+y1) & 0xf8) >> 1) | (LIMIT(g+y1) >> 6);
		return 4;
	case VIDEO_PALETTE_RGB565:
		*rgb++ = ((LIMIT(g+y) & 0xfc) << 3) | (LIMIT(b+y) >> 3);
		*rgb++ = (LIMIT(r+y) & 0xf8) | (LIMIT(g+y) >> 5);
		*rgb++ = ((LIMIT(g+y1) & 0xfc) << 3) | (LIMIT(b+y1) >> 3);
		*rgb = (LIMIT(r+y1) & 0xf8) | (LIMIT(g+y1) >> 5);
		return 4;
	case VIDEO_PALETTE_RGB24:
		if (mmap_kludge) {
			*rgb++ = LIMIT(b+y);
			*rgb++ = LIMIT(g+y);
			*rgb++ = LIMIT(r+y);
			*rgb++ = LIMIT(b+y1);
			*rgb++ = LIMIT(g+y1);
			*rgb = LIMIT(r+y1);
		} else {
			*rgb++ = LIMIT(r+y);
			*rgb++ = LIMIT(g+y);
			*rgb++ = LIMIT(b+y);
			*rgb++ = LIMIT(r+y1);
			*rgb++ = LIMIT(g+y1);
			*rgb = LIMIT(b+y1);
		}
		return 6;
	case VIDEO_PALETTE_RGB32:
		if (mmap_kludge) {
			*rgb++ = LIMIT(b+y);
			*rgb++ = LIMIT(g+y);
			*rgb++ = LIMIT(r+y);
			rgb++;
			*rgb++ = LIMIT(b+y1);
			*rgb++ = LIMIT(g+y1);
			*rgb = LIMIT(r+y1);
		} else {
			*rgb++ = LIMIT(r+y);
			*rgb++ = LIMIT(g+y);
			*rgb++ = LIMIT(b+y);
			rgb++;
			*rgb++ = LIMIT(r+y1);
			*rgb++ = LIMIT(g+y1);
			*rgb = LIMIT(b+y1);
		}
		return 8;
	case VIDEO_PALETTE_GREY:
		*rgb++ = y;
		*rgb = y1;
		return 2;
	case VIDEO_PALETTE_YUV422:
	case VIDEO_PALETTE_YUYV:
		*rgb++ = y;
		*rgb++ = u;
		*rgb++ = y1;
		*rgb = v;
		return 4;
	case VIDEO_PALETTE_UYVY:
		*rgb++ = u;
		*rgb++ = y;
		*rgb++ = v;
		*rgb = y1;
		return 4;
	default:
		DBG("Empty: %d\n", out_fmt);
		return 0;
	}
}