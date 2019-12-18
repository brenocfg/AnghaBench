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
typedef  int /*<<< orphan*/  u32 ;
struct mode_registers {int /*<<< orphan*/  bpp24_133; int /*<<< orphan*/  bpp16_133; int /*<<< orphan*/  bpp8_133; int /*<<< orphan*/  bpp24_100; int /*<<< orphan*/  bpp16_100; int /*<<< orphan*/  bpp8_100; } ;
struct i810fb_par {int mem_freq; struct mode_registers regs; } ;
struct fb_var_screeninfo {int bits_per_pixel; } ;

/* Variables and functions */

u32 i810_get_watermark(struct fb_var_screeninfo *var,
		       struct i810fb_par *par)
{
	struct mode_registers *params = &par->regs;
	u32 wmark = 0;
	
	if (par->mem_freq == 100) {
		switch (var->bits_per_pixel) {
		case 8:
			wmark = params->bpp8_100;
			break;
		case 16:
			wmark = params->bpp16_100;
			break;
		case 24:
		case 32:
			wmark = params->bpp24_100;
		}
	} else {					
		switch (var->bits_per_pixel) {
		case 8:
			wmark = params->bpp8_133;
			break;
		case 16:
			wmark = params->bpp16_133;
			break;
		case 24:
		case 32:
			wmark = params->bpp24_133;
		}
	}
	return wmark;
}