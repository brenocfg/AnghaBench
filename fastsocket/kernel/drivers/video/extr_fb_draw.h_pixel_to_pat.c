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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static inline unsigned long
pixel_to_pat( u32 bpp, u32 pixel)
{
	switch (bpp) {
	case 1:
		return 0xfffffffful*pixel;
	case 2:
		return 0x55555555ul*pixel;
	case 4:
		return 0x11111111ul*pixel;
	case 8:
		return 0x01010101ul*pixel;
	case 12:
		return 0x01001001ul*pixel;
	case 16:
		return 0x00010001ul*pixel;
	case 24:
		return 0x01000001ul*pixel;
	case 32:
		return 0x00000001ul*pixel;
	default:
		panic("pixel_to_pat(): unsupported pixelformat\n");
    }
}