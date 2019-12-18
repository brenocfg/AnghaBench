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
struct corgi_lcd {int limit_mask; } ;
struct TYPE_2__ {int brightness; scalar_t__ power; scalar_t__ fb_blank; } ;
struct backlight_device {TYPE_1__ props; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CORGIBL_BATTLOW ; 
 int CORGIBL_SUSPENDED ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int corgi_bl_set_intensity (struct corgi_lcd*,int) ; 
 int corgibl_flags ; 
 struct corgi_lcd* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int corgi_bl_update_status(struct backlight_device *bd)
{
	struct corgi_lcd *lcd = dev_get_drvdata(&bd->dev);
	int intensity = bd->props.brightness;

	if (bd->props.power != FB_BLANK_UNBLANK)
		intensity = 0;

	if (bd->props.fb_blank != FB_BLANK_UNBLANK)
		intensity = 0;

	if (corgibl_flags & CORGIBL_SUSPENDED)
		intensity = 0;

	if ((corgibl_flags & CORGIBL_BATTLOW) && intensity > lcd->limit_mask)
		intensity = lcd->limit_mask;

	return corgi_bl_set_intensity(lcd, intensity);
}