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
struct TYPE_4__ {int brightness; scalar_t__ AC50Hz; scalar_t__ flip; scalar_t__ mirror; scalar_t__ whitebal; scalar_t__ saturation; scalar_t__ hue; scalar_t__ gamma; scalar_t__ contrast; scalar_t__ sharpness; scalar_t__ backlight; } ;
struct TYPE_3__ {int brightness; scalar_t__ whitebal; scalar_t__ saturation; scalar_t__ hue; scalar_t__ gamma; scalar_t__ contrast; scalar_t__ sharpness; scalar_t__ backlight; } ;
struct sd {int /*<<< orphan*/  dev_post_unset_alt; int /*<<< orphan*/  dev_init_pre_alt; int /*<<< orphan*/  dev_configure_alt; int /*<<< orphan*/  dev_init_at_startup; int /*<<< orphan*/  dev_camera_settings; TYPE_2__ vmax; TYPE_1__ vcur; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ov9655_camera_settings ; 
 int /*<<< orphan*/  ov9655_configure_alt ; 
 int /*<<< orphan*/  ov9655_init_at_startup ; 
 int /*<<< orphan*/  ov9655_init_pre_alt ; 
 int /*<<< orphan*/  ov9655_post_unset_alt ; 

void ov9655_init_settings(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->vcur.backlight  =   0;
	sd->vcur.brightness = 128;
	sd->vcur.sharpness  =   0;
	sd->vcur.contrast   =   0;
	sd->vcur.gamma      =   0;
	sd->vcur.hue        =   0;
	sd->vcur.saturation =   0;
	sd->vcur.whitebal   =   0;

	sd->vmax.backlight  =   0;
	sd->vmax.brightness = 255;
	sd->vmax.sharpness  =   0;
	sd->vmax.contrast   =   0;
	sd->vmax.gamma      =   0;
	sd->vmax.hue        =   0 + 1;
	sd->vmax.saturation =   0;
	sd->vmax.whitebal   =   0;
	sd->vmax.mirror     = 0;
	sd->vmax.flip       = 0;
	sd->vmax.AC50Hz     = 0;

	sd->dev_camera_settings = ov9655_camera_settings;
	sd->dev_init_at_startup = ov9655_init_at_startup;
	sd->dev_configure_alt   = ov9655_configure_alt;
	sd->dev_init_pre_alt    = ov9655_init_pre_alt;
	sd->dev_post_unset_alt  = ov9655_post_unset_alt;
}