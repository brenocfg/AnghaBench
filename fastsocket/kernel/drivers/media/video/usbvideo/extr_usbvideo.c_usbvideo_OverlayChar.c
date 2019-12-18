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
struct uvd {long paletteBits; } ;
struct usbvideo_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGB24_PUTPIXEL (struct usbvideo_frame*,int,int,int,int,int) ; 
 long VIDEO_PALETTE_RGB24 ; 

__attribute__((used)) static void usbvideo_OverlayChar(struct uvd *uvd, struct usbvideo_frame *frame,
				 int x, int y, int ch)
{
	static const unsigned short digits[16] = {
		0xF6DE, /* 0 */
		0x2492, /* 1 */
		0xE7CE, /* 2 */
		0xE79E, /* 3 */
		0xB792, /* 4 */
		0xF39E, /* 5 */
		0xF3DE, /* 6 */
		0xF492, /* 7 */
		0xF7DE, /* 8 */
		0xF79E, /* 9 */
		0x77DA, /* a */
		0xD75C, /* b */
		0xF24E, /* c */
		0xD6DC, /* d */
		0xF34E, /* e */
		0xF348  /* f */
	};
	unsigned short digit;
	int ix, iy;

	if ((uvd == NULL) || (frame == NULL))
		return;

	if (ch >= '0' && ch <= '9')
		ch -= '0';
	else if (ch >= 'A' && ch <= 'F')
		ch = 10 + (ch - 'A');
	else if (ch >= 'a' && ch <= 'f')
		ch = 10 + (ch - 'a');
	else
		return;
	digit = digits[ch];

	for (iy=0; iy < 5; iy++) {
		for (ix=0; ix < 3; ix++) {
			if (digit & 0x8000) {
				if (uvd->paletteBits & (1L << VIDEO_PALETTE_RGB24)) {
/* TODO */				RGB24_PUTPIXEL(frame, x+ix, y+iy, 0xFF, 0xFF, 0xFF);
				}
			}
			digit = digit << 1;
		}
	}
}