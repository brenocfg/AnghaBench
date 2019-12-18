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
struct platform_device {int dummy; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lcd_device_unregister (struct lcd_device*) ; 
 struct lcd_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int jornada_lcd_remove(struct platform_device *pdev)
{
	struct lcd_device *lcd_device = platform_get_drvdata(pdev);

	lcd_device_unregister(lcd_device);

	return 0;
}