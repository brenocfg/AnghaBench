#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* s68k_regs; } ;
struct TYPE_3__ {scalar_t__ renderer; } ;

/* Variables and functions */
 TYPE_2__* Pico_mcd ; 
 scalar_t__ RT_16BIT ; 
 TYPE_1__ currentConfig ; 
 scalar_t__ g_screen_ptr ; 
 unsigned int p (int) ; 

__attribute__((used)) static void draw_cd_leds(void)
{
	int led_reg, pitch, scr_offs, led_offs;
	led_reg = Pico_mcd->s68k_regs[0];

	pitch = 320;
	led_offs = 4;
	scr_offs = pitch * 2 + 4;

	if (currentConfig.renderer != RT_16BIT) {
	#define p(x) px[(x) >> 2]
		// 8-bit modes
		unsigned int *px = (unsigned int *)((char *)g_screen_ptr + scr_offs);
		unsigned int col_g = (led_reg & 2) ? 0xc0c0c0c0 : 0xe0e0e0e0;
		unsigned int col_r = (led_reg & 1) ? 0xd0d0d0d0 : 0xe0e0e0e0;
		p(pitch*0) = p(pitch*1) = p(pitch*2) = col_g;
		p(pitch*0 + led_offs) = p(pitch*1 + led_offs) = p(pitch*2 + led_offs) = col_r;
	#undef p
	} else {
	#define p(x) px[(x)*2 >> 2] = px[((x)*2 >> 2) + 1]
		// 16-bit modes
		unsigned int *px = (unsigned int *)((short *)g_screen_ptr + scr_offs);
		unsigned int col_g = (led_reg & 2) ? 0x06000600 : 0;
		unsigned int col_r = (led_reg & 1) ? 0xc000c000 : 0;
		p(pitch*0) = p(pitch*1) = p(pitch*2) = col_g;
		p(pitch*0 + led_offs) = p(pitch*1 + led_offs) = p(pitch*2 + led_offs) = col_r;
	#undef p
	}
}