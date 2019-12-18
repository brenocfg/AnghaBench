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
struct lcd_device {int /*<<< orphan*/  dev; } ;
struct corgi_lcd {int power; } ;

/* Variables and functions */
 scalar_t__ POWER_IS_ON (int) ; 
 int /*<<< orphan*/  corgi_lcd_power_off (struct corgi_lcd*) ; 
 int /*<<< orphan*/  corgi_lcd_power_on (struct corgi_lcd*) ; 
 struct corgi_lcd* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int corgi_lcd_set_power(struct lcd_device *ld, int power)
{
	struct corgi_lcd *lcd = dev_get_drvdata(&ld->dev);

	if (POWER_IS_ON(power) && !POWER_IS_ON(lcd->power))
		corgi_lcd_power_on(lcd);

	if (!POWER_IS_ON(power) && POWER_IS_ON(lcd->power))
		corgi_lcd_power_off(lcd);

	lcd->power = power;
	return 0;
}