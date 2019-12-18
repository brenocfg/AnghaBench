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
typedef  int UBYTE ;

/* Variables and functions */
 int ANTIC_DMACTL ; 
 int ANTIC_ypos ; 
#define  A_BOLD 129 
#define  A_REVERSE 128 
 int GTIA_COLPF0 ; 
 int GTIA_COLPF1 ; 
 int GTIA_COLPF2 ; 
 int GTIA_COLPF3 ; 
 int LIGHT_THRESHOLD ; 
 int** curses_screen ; 

void curses_display_line(int anticmode, const UBYTE *screendata)
{
	int y;
	int *p;
	int w;
	if (ANTIC_ypos < 32 || ANTIC_ypos >= 224)
		return;
	y = (ANTIC_ypos >> 3) - 4;
	p = &(curses_screen[y][0]);
	switch (anticmode) {
	case 2:
	case 3:
	case 4:
	case 5:
		switch (ANTIC_DMACTL & 3) {
		case 1:
			p += 4;
			w = 32;
			break;
		case 2:
			w = 40;
			break;
		case 3:
			screendata += 4;
			w = 40;
			break;
		default:
			return;
		}
		do {
			static const int offset[8] = {
				0x20,                       /* 0x00-0x1f: Numbers + !"$% etc. */
				0x20,                       /* 0x20-0x3f: Upper Case Characters */
				A_BOLD,                     /* 0x40-0x5f: Control Characters */
				0,                          /* 0x60-0x7f: Lower Case Characters */
				-0x80 + 0x20 + A_REVERSE,   /* 0x80-0x9f: Numbers + !"$% etc. */
				-0x80 + 0x20 + A_REVERSE,   /* 0xa0-0xbf: Upper Case Characters */
				-0x80 + A_BOLD + A_REVERSE, /* 0xc0-0xdf: Control Characters */
				-0x80 + A_REVERSE           /* 0xe0-0xff: Lower Case Characters */
			};
			UBYTE c = *screendata++;
			/* PDCurses prints '\x7f' as "^?".
			   This causes problems if this is the last character in line.
			   Use bold '>' for Atari's Tab symbol (filled right-pointing triangle). */
			if (c == 0x7f)
				*p = '>' + A_BOLD;
			else if (c == 0xff)
				*p = '>' + A_BOLD + A_REVERSE;
			else
				*p = c + offset[c >> 5];
			p++;
		} while (--w);
		break;
	case 6:
	case 7:
		switch (ANTIC_DMACTL & 3) {
		case 1:
			p += 12;
			w = 16;
			break;
		case 2:
			p += 10;
			w = 20;
			break;
		case 3:
			p += 8;
			w = 24;
			break;
		default:
			return;
		}
		{
#define LIGHT_THRESHOLD 0x0c
			int light[4];
			light[0] = (GTIA_COLPF0 & 0x0e) >= LIGHT_THRESHOLD ? 0x20 + A_BOLD : 0x20;
			light[1] = (GTIA_COLPF1 & 0x0e) >= LIGHT_THRESHOLD ? -0x40 + 0x20 + A_BOLD : -0x40 + 0x20;
			light[2] = (GTIA_COLPF2 & 0x0e) >= LIGHT_THRESHOLD ? -0x80 + 0x20 + A_BOLD : -0x80 + 0x20;
			light[3] = (GTIA_COLPF3 & 0x0e) >= LIGHT_THRESHOLD ? -0xc0 + 0x20 + A_BOLD : -0xc0 + 0x20;
			do {
				*p++ = *screendata + light[*screendata >> 6];
				screendata++;
			} while (--w);
		}
		break;
	default:
		break;
	}
}