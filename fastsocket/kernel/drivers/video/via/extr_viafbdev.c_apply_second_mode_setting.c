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
struct fb_var_screeninfo {int xres; int left_margin; int right_margin; int hsync_len; int yres; int upper_margin; int lower_margin; int vsync_len; int xres_virtual; int bits_per_pixel; unsigned long pixclock; int /*<<< orphan*/  yres_virtual; } ;

/* Variables and functions */
 int viafb_bpp1 ; 
 int /*<<< orphan*/  viafb_get_refresh (int,int,int) ; 
 int /*<<< orphan*/  viafb_refresh1 ; 
 int viafb_second_virtual_xres ; 
 int /*<<< orphan*/  viafb_second_virtual_yres ; 
 int viafb_second_xres ; 
 int viafb_second_yres ; 

__attribute__((used)) static void apply_second_mode_setting(struct fb_var_screeninfo
	*sec_var)
{
	u32 htotal, vtotal, long_refresh;

	htotal = sec_var->xres + sec_var->left_margin +
		sec_var->right_margin + sec_var->hsync_len;
	vtotal = sec_var->yres + sec_var->upper_margin +
		sec_var->lower_margin + sec_var->vsync_len;
	if ((sec_var->xres_virtual * (sec_var->bits_per_pixel >> 3)) & 0x1F) {
		/*Is 32 bytes alignment? */
		/*32 pixel alignment */
		sec_var->xres_virtual = (sec_var->xres_virtual + 31) & ~31;
	}

	htotal = sec_var->xres + sec_var->left_margin +
		sec_var->right_margin + sec_var->hsync_len;
	vtotal = sec_var->yres + sec_var->upper_margin +
		sec_var->lower_margin + sec_var->vsync_len;
	long_refresh = 1000000000UL / sec_var->pixclock * 1000;
	long_refresh /= (htotal * vtotal);

	viafb_second_xres = sec_var->xres;
	viafb_second_yres = sec_var->yres;
	viafb_second_virtual_xres = sec_var->xres_virtual;
	viafb_second_virtual_yres = sec_var->yres_virtual;
	viafb_bpp1 = sec_var->bits_per_pixel;
	viafb_refresh1 = viafb_get_refresh(sec_var->xres, sec_var->yres,
		long_refresh);
}