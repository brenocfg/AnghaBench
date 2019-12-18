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
typedef  int u32 ;
struct fb_var_screeninfo {int pixclock; scalar_t__ xres; } ;
struct TYPE_3__ {scalar_t__ xres; } ;
struct TYPE_4__ {TYPE_1__ ct; } ;
struct atyfb_par {scalar_t__ lcd_table; int lcd_pixclock; TYPE_2__ pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_GEN_CNTL ; 
 int LCD_ON ; 
 int aty_ld_lcd (int /*<<< orphan*/ ,struct atyfb_par*) ; 

__attribute__((used)) static u32 atyfb_get_pixclock(struct fb_var_screeninfo *var,
			      struct atyfb_par *par)
{
	u32 pixclock = var->pixclock;
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	u32 lcd_on_off;
	par->pll.ct.xres = 0;
	if (par->lcd_table != 0) {
		lcd_on_off = aty_ld_lcd(LCD_GEN_CNTL, par);
		if (lcd_on_off & LCD_ON) {
			par->pll.ct.xres = var->xres;
			pixclock = par->lcd_pixclock;
		}
	}
#endif
	return pixclock;
}