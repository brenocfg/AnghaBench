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
 unsigned char* fontdata8x8 ; 

void basic_text_out16_nf(void *fb, int w, int x, int y, const char *text)
{
	int i, l;
	unsigned short *screen;
	unsigned short val = 0xffff;

	screen = (unsigned short *)fb + x + y * w;
	for (i = 0; ; i++, screen += 8)
	{
		char c = text[i];
		if (c == 0)
			break;
		if (c == ' ')
			continue;

		for (l = 0; l < 8; l++)
		{
			unsigned char fd = fontdata8x8[c * 8 + l];
			unsigned short *s = screen + l * w;
			unsigned char fd1, fdp = 0;

			if (fd&0x80) s[0] = val;
			if (fd&0x40) s[1] = val;
			if (fd&0x20) s[2] = val;
			if (fd&0x10) s[3] = val;
			if (fd&0x08) s[4] = val;
			if (fd&0x04) s[5] = val;
			if (fd&0x02) s[6] = val;
			if (fd&0x01) s[7] = val;

			// draw "shadow" (RGB1555 compatible)
			if (l > 0)
				fdp = fontdata8x8[c * 8 + l - 1];

			for (fd1 = 0x80; fd1 != 0; fd1 >>= 1, s++)
				if (!(fd & (fd1 >> 1)) && ((fdp | fd) & fd1))
					s[1] = (s[1] >> 1) & 0x39ef;
		}
	}
}