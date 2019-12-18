#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_lcd {TYPE_1__* us; struct plat_lcd_data* pdata; } ;
struct plat_lcd_data {int (* match_fb ) (struct plat_lcd_data*,struct fb_info*) ;} ;
struct lcd_device {int dummy; } ;
struct fb_info {scalar_t__ device; } ;
struct TYPE_2__ {scalar_t__ parent; } ;

/* Variables and functions */
 int stub1 (struct plat_lcd_data*,struct fb_info*) ; 
 struct platform_lcd* to_our_lcd (struct lcd_device*) ; 

__attribute__((used)) static int platform_lcd_match(struct lcd_device *lcd, struct fb_info *info)
{
	struct platform_lcd *plcd = to_our_lcd(lcd);
	struct plat_lcd_data *pdata = plcd->pdata;

	if (pdata->match_fb)
		return pdata->match_fb(pdata, info);

	return plcd->us->parent == info->device;
}