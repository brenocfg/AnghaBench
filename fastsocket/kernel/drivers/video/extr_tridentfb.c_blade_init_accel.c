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
struct tridentfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  writemmr (struct tridentfb_par*,int,int) ; 

__attribute__((used)) static void blade_init_accel(struct tridentfb_par *par, int pitch, int bpp)
{
	int v1 = (pitch >> 3) << 20;
	int tmp = bpp == 24 ? 2 : (bpp >> 4);
	int v2 = v1 | (tmp << 29);

	writemmr(par, 0x21C0, v2);
	writemmr(par, 0x21C4, v2);
	writemmr(par, 0x21B8, v2);
	writemmr(par, 0x21BC, v2);
	writemmr(par, 0x21D0, v1);
	writemmr(par, 0x21D4, v1);
	writemmr(par, 0x21C8, v1);
	writemmr(par, 0x21CC, v1);
	writemmr(par, 0x216C, 0);
}