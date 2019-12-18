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
struct platform_lcd {int power; TYPE_1__* pdata; scalar_t__ suspended; } ;
struct lcd_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_power ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 struct platform_lcd* to_our_lcd (struct lcd_device*) ; 

__attribute__((used)) static int platform_lcd_set_power(struct lcd_device *lcd, int power)
{
	struct platform_lcd *plcd = to_our_lcd(lcd);
	int lcd_power = 1;

	if (power == FB_BLANK_POWERDOWN || plcd->suspended)
		lcd_power = 0;

	plcd->pdata->set_power(plcd->pdata, lcd_power);
	plcd->power = power;

	return 0;
}