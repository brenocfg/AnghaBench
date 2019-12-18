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
struct backlight_device {int dummy; } ;
struct adxbl {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ADX_BACKLIGHT_BRIGHTNESS ; 
 struct adxbl* bl_get_data (struct backlight_device*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int adx_backlight_get_brightness(struct backlight_device *bldev)
{
	struct adxbl *bl = bl_get_data(bldev);
	u32 brightness;

	brightness = readl(bl->base + ADX_BACKLIGHT_BRIGHTNESS);
	return brightness & 0xff;
}