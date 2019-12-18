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
struct TYPE_4__ {int backlight; int brightness; int sharpness; int contrast; int gamma; int whitebal; int mirror; int flip; int AC50Hz; scalar_t__ saturation; scalar_t__ hue; } ;
struct TYPE_3__ {int brightness; int sharpness; int saturation; int AC50Hz; scalar_t__ flip; scalar_t__ mirror; scalar_t__ whitebal; scalar_t__ hue; scalar_t__ gamma; scalar_t__ contrast; scalar_t__ backlight; } ;
struct sd {int /*<<< orphan*/  dev_post_unset_alt; int /*<<< orphan*/  dev_init_pre_alt; int /*<<< orphan*/  dev_configure_alt; int /*<<< orphan*/  dev_init_at_startup; int /*<<< orphan*/  dev_camera_settings; TYPE_2__ vmax; TYPE_1__ vcur; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mi2020_camera_settings ; 
 int /*<<< orphan*/  mi2020_configure_alt ; 
 int /*<<< orphan*/  mi2020_init_at_startup ; 
 int /*<<< orphan*/  mi2020_init_pre_alt ; 
 int /*<<< orphan*/  mi2020_post_unset_alt ; 

void mi2020_init_settings(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->vcur.backlight  =  0;
	sd->vcur.brightness = 70;
	sd->vcur.sharpness  = 20;
	sd->vcur.contrast   =  0;
	sd->vcur.gamma      =  0;
	sd->vcur.hue        =  0;
	sd->vcur.saturation = 60;
	sd->vcur.whitebal   =  0; /* 50, not done by hardware */
	sd->vcur.mirror = 0;
	sd->vcur.flip   = 0;
	sd->vcur.AC50Hz = 1;

	sd->vmax.backlight  =  64;
	sd->vmax.brightness = 128;
	sd->vmax.sharpness  =  40;
	sd->vmax.contrast   =   3;
	sd->vmax.gamma      =   2;
	sd->vmax.hue        =   0 + 1; /* 200, not done by hardware */
	sd->vmax.saturation =   0;     /* 100, not done by hardware */
	sd->vmax.whitebal   =   2;     /* 100, not done by hardware */
	sd->vmax.mirror = 1;
	sd->vmax.flip   = 1;
	sd->vmax.AC50Hz = 1;

	sd->dev_camera_settings = mi2020_camera_settings;
	sd->dev_init_at_startup = mi2020_init_at_startup;
	sd->dev_configure_alt   = mi2020_configure_alt;
	sd->dev_init_pre_alt    = mi2020_init_pre_alt;
	sd->dev_post_unset_alt  = mi2020_post_unset_alt;
}