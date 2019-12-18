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
struct tridentfb_par {unsigned char eng_oper; } ;

/* Variables and functions */
 int /*<<< orphan*/  t_outb (struct tridentfb_par*,int,int) ; 
 int /*<<< orphan*/  writemmr (struct tridentfb_par*,int,int) ; 

__attribute__((used)) static void xp_init_accel(struct tridentfb_par *par, int pitch, int bpp)
{
	unsigned char x = bpp == 24 ? 3 : (bpp >> 4);
	int v1 = pitch << (bpp == 24 ? 20 : (18 + x));

	switch (pitch << (bpp >> 3)) {
	case 8192:
	case 512:
		x |= 0x00;
		break;
	case 1024:
		x |= 0x04;
		break;
	case 2048:
		x |= 0x08;
		break;
	case 4096:
		x |= 0x0C;
		break;
	}

	t_outb(par, x, 0x2125);

	par->eng_oper = x | 0x40;

	writemmr(par, 0x2154, v1);
	writemmr(par, 0x2150, v1);
	t_outb(par, 3, 0x2126);
}