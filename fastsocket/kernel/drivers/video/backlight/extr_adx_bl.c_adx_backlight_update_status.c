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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int state; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct adxbl {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ADX_BACKLIGHT_BRIGHTNESS ; 
 scalar_t__ ADX_BACKLIGHT_CONTROL ; 
 int /*<<< orphan*/  ADX_BACKLIGHT_CONTROL_ENABLE ; 
 int BL_CORE_FBBLANK ; 
 struct adxbl* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int adx_backlight_update_status(struct backlight_device *bldev)
{
	struct adxbl *bl = bl_get_data(bldev);
	u32 value;

	value = bldev->props.brightness;
	writel(value, bl->base + ADX_BACKLIGHT_BRIGHTNESS);

	value = readl(bl->base + ADX_BACKLIGHT_CONTROL);

	if (bldev->props.state & BL_CORE_FBBLANK)
		value &= ~ADX_BACKLIGHT_CONTROL_ENABLE;
	else
		value |= ADX_BACKLIGHT_CONTROL_ENABLE;

	writel(value, bl->base + ADX_BACKLIGHT_CONTROL);

	return 0;
}