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
 scalar_t__ PICO_PEN_ADJUST_X ; 
 int PICO_PEN_ADJUST_Y ; 
 scalar_t__ VRAM_STUFF ; 
 scalar_t__ blit_16bit_mode ; 
 scalar_t__ pico_inp_mode ; 
 scalar_t__ pico_pen_x ; 
 int pico_pen_y ; 

__attribute__((used)) static void draw_pico_ptr(void)
{
	unsigned char *p = (unsigned char *)VRAM_STUFF + 16;

	// only if pen enabled and for 8bit mode
	if (pico_inp_mode == 0 || blit_16bit_mode) return;

	p += 512 * (pico_pen_y + PICO_PEN_ADJUST_Y);
	p += pico_pen_x + PICO_PEN_ADJUST_X;
	p[  -1] = 0xe0; p[   0] = 0xf0; p[   1] = 0xe0;
	p[ 511] = 0xf0; p[ 512] = 0xf0; p[ 513] = 0xf0;
	p[1023] = 0xe0; p[1024] = 0xf0; p[1025] = 0xe0;
}