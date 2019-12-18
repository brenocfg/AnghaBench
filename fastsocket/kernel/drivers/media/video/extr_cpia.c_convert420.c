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

__attribute__((used)) static int convert420(unsigned char *yuv, unsigned char *rgb, int out_fmt,
		      int linesize, int mmap_kludge)
{
	int y, u, v, r, g, b, y1;

	/* Odd lines use the same u and v as the previous line.
	 * Because of compression, it is necessary to get this
	 * information from the decoded image. */
	switch(out_fmt) {
	case VIDEO_PALETTE_RGB555:
		y = (*yuv++ - 16) * 76310;
		y1 = (*yuv - 16) * 76310;
		r = ((*(rgb+1-linesize)) & 0x7c) << 1;
		g = ((*(rgb-linesize)) & 0xe0) >> 4 |
		    ((*(rgb+1-linesize)) & 0x03) << 6;
		b = ((*(rgb-linesize)) & 0x1f) << 3;
		u = (-53294 * r - 104635 * g + 157929 * b) / 5756495;
		v = (157968 * r - 132278 * g - 25690 * b) / 5366159;
		r = 104635 * v;
		g = -25690 * u - 53294 * v;
		b = 132278 * u;
		*rgb++ = ((LIMIT(g+y) & 0xf8) << 2) | (LIMIT(b+y) >> 3);
		*rgb++ = ((LIMIT(r+y) & 0xf8) >> 1) | (LIMIT(g+y) >> 6);
		*rgb++ = ((LIMIT(g+y1) & 0xf8) << 2) | (LIMIT(b+y1) >> 3);
		*rgb = ((LIMIT(r+y1) & 0xf8) >> 1) | (LIMIT(g+y1) >> 6);
		return 4;
	case VIDEO_PALETTE_RGB565:
		y = (*yuv++ - 16) * 76310;
		y1 = (*yuv - 16) * 76310;
		r = (*(rgb+1-linesize)) & 0xf8;
		g = ((*(rgb-linesize)) & 0xe0) >> 3 |
		    ((*(rgb+1-linesize)) & 0x07) << 5;
		b = ((*(rgb-linesize)) & 0x1f) << 3;
		u = (-53294 * r - 104635 * g + 157929 * b) / 5756495;
		v = (157968 * r - 132278 * g - 25690 * b) / 5366159;
		r = 104635 * v;
		g = -25690 * u - 53294 * v;
		b = 132278 * u;
		*rgb++ = ((LIMIT(g+y) & 0xfc) << 3) | (LIMIT(b+y) >> 3);
		*rgb++ = (LIMIT(r+y) & 0xf8) | (LIMIT(g+y) >> 5);
		*rgb++ = ((LIMIT(g+y1) & 0xfc) << 3) | (LIMIT(b+y1) >> 3);
		*rgb = (LIMIT(r+y1) & 0xf8) | (LIMIT(g+y1) >> 5);
		return 4;
		break;
	case VIDEO_PALETTE_RGB24:
	case VIDEO_PALETTE_RGB32:
		y = (*yuv++ - 16) * 76310;
		y1 = (*yuv - 16) * 76310;
		if (mmap_kludge) {
			r = *(rgb+2-linesize);
			g = *(rgb+1-linesize);
			b = *(rgb-linesize);
		} else {
			r = *(rgb-linesize);
			g = *(rgb+1-linesize);
			b = *(rgb+2-linesize);
		}
		u = (-53294 * r - 104635 * g + 157929 * b) / 5756495;
		v = (157968 * r - 132278 * g - 25690 * b) / 5366159;
		r = 104635 * v;
		g = -25690 * u + -53294 * v;
		b = 132278 * u;
		if (mmap_kludge) {
			*rgb++ = LIMIT(b+y);
			*rgb++ = LIMIT(g+y);
			*rgb++ = LIMIT(r+y);
			if(out_fmt == VIDEO_PALETTE_RGB32)
				rgb++;
			*rgb++ = LIMIT(b+y1);
			*rgb++ = LIMIT(g+y1);
			*rgb = LIMIT(r+y1);
		} else {
			*rgb++ = LIMIT(r+y);
			*rgb++ = LIMIT(g+y);
			*rgb++ = LIMIT(b+y);
			if(out_fmt == VIDEO_PALETTE_RGB32)
				rgb++;
			*rgb++ = LIMIT(r+y1);
			*rgb++ = LIMIT(g+y1);
			*rgb = LIMIT(b+y1);
		}
		if(out_fmt == VIDEO_PALETTE_RGB32)
			return 8;
		return 6;
	case VIDEO_PALETTE_YUV422:
	case VIDEO_PALETTE_YUYV:
		y = *yuv++;
		u = *(rgb+1-linesize);
		y1 = *yuv;
		v = *(rgb+3-linesize);
		*rgb++ = y;
		*rgb++ = u;
		*rgb++ = y1;
		*rgb = v;
		return 4;
	case VIDEO_PALETTE_UYVY:
		u = *(rgb-linesize);
		y = *yuv++;
		v = *(rgb+2-linesize);
		y1 = *yuv;
		*rgb++ = u;
		*rgb++ = y;
		*rgb++ = v;
		*rgb = y1;
		return 4;
	case VIDEO_PALETTE_GREY:
		*rgb++ = *yuv++;
		*rgb = *yuv;
		return 2;
	default:
		DBG("Empty: %d\n", out_fmt);
		return 0;
	}
}