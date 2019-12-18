#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int backlight; int brightness; int whitebal; int contrast; int saturation; int sharpness; int hue; int gamma; int mirror; int flip; } ;
struct TYPE_5__ {int backlight; int brightness; int whitebal; int contrast; int saturation; int sharpness; int hue; int gamma; } ;
struct TYPE_4__ {int backlight; int brightness; int sharpness; int gamma; int contrast; int saturation; int hue; int whitebal; scalar_t__ mirror; scalar_t__ flip; } ;
struct sd {int mirrorMask; int swapRB; TYPE_3__ vold; TYPE_2__ vmax; TYPE_1__ vcur; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  c28 ; 
 int /*<<< orphan*/  c50 ; 
 int /*<<< orphan*/  ca8 ; 
 int /*<<< orphan*/  ctrl_in (struct gspca_dev*,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov2640_camera_settings(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	s32 backlight = sd->vcur.backlight;
	s32 bright = sd->vcur.brightness;
	s32 sharp  = sd->vcur.sharpness;
	s32 gam    = sd->vcur.gamma;
	s32 cntr   = sd->vcur.contrast;
	s32 sat    = sd->vcur.saturation;
	s32 hue    = sd->vcur.hue;
	s32 wbal   = sd->vcur.whitebal;
	s32 mirror = (((sd->vcur.mirror > 0) ^ sd->mirrorMask) == 0);
	s32 flip   = (((sd->vcur.flip   > 0) ^ sd->mirrorMask) == 0);

	if (backlight != sd->vold.backlight) {
		/* No sd->vold.backlight=backlight; (to be done again later) */
		if (backlight < 0 || backlight > sd->vmax.backlight)
			backlight = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6001                 , 0x00ff,
				0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x601e + backlight     , 0x0024,
				0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x601e + backlight - 10, 0x0025,
				0, NULL);
	}

	if (bright != sd->vold.brightness) {
		sd->vold.brightness = bright;
		if (bright < 0 || bright > sd->vmax.brightness)
			bright = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000         , 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6009         , 0x007c, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + bright, 0x007d, 0, NULL);
	}

	if (wbal != sd->vold.whitebal) {
		sd->vold.whitebal = wbal;
		if (wbal < 0 || wbal > sd->vmax.whitebal)
			wbal = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000       , 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6003       , 0x007c, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + wbal, 0x007d, 0, NULL);
	}

	if (cntr != sd->vold.contrast) {
		sd->vold.contrast = cntr;
		if (cntr < 0 || cntr > sd->vmax.contrast)
			cntr = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000       , 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6007       , 0x007c, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + cntr, 0x007d, 0, NULL);
	}

	if (sat != sd->vold.saturation) {
		sd->vold.saturation = sat;
		if (sat < 0 || sat > sd->vmax.saturation)
			sat = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000      , 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6001      , 0x007c, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + sat, 0x007d, 0, NULL);
	}

	if (sharp != sd->vold.sharpness) {
		sd->vold.sharpness = sharp;
		if (sharp < 0 || sharp > sd->vmax.sharpness)
			sharp = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000        , 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6001        , 0x0092, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x60c0 + sharp, 0x0093, 0, NULL);
	}

	if (hue != sd->vold.hue) {
		sd->vold.hue = hue;
		if (hue < 0 || hue > sd->vmax.hue)
			hue = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000     , 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6002     , 0x007c, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + hue * (hue < 255), 0x007d,
				0, NULL);
		if (hue >= 255)
			sd->swapRB = 1;
		else
			sd->swapRB = 0;
	}

	if (gam != sd->vold.gamma) {
		sd->vold.gamma = gam;
		if (gam < 0 || gam > sd->vmax.gamma)
			gam = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000      , 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6008      , 0x007c, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + gam, 0x007d, 0, NULL);
	}

	if (mirror != sd->vold.mirror || flip != sd->vold.flip) {
		sd->vold.mirror = mirror;
		sd->vold.flip   = flip;

		mirror = 0x80 * mirror;
		ctrl_out(gspca_dev, 0x40, 1, 0x6001, 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000, 0x8004, 0, NULL);
		ctrl_in(gspca_dev, 0xc0, 2, 0x6000, 0x8004, 1, c28);
		ctrl_out(gspca_dev, 0x40, 1, 0x6028 + mirror, 0x0004, 0, NULL);

		flip = 0x50 * flip + mirror;
		ctrl_out(gspca_dev, 0x40, 1, 0x6001, 0x00ff, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000, 0x8004, 0, NULL);
		ctrl_in(gspca_dev, 0xc0, 2, 0x6000, 0x8004, 1, ca8);
		ctrl_out(gspca_dev, 0x40, 1, 0x6028 + flip, 0x0004, 0, NULL);

		ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0000, 1, c50);
	}

	if (backlight != sd->vold.backlight) {
		sd->vold.backlight = backlight;

		ctrl_out(gspca_dev, 0x40, 1, 0x6001                 , 0x00ff,
				0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x601e + backlight     , 0x0024,
				0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x601e + backlight - 10, 0x0025,
				0, NULL);
	}

	return 0;
}