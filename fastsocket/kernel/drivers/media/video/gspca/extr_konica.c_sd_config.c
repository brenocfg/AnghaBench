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
struct usb_device_id {int dummy; } ;
struct sd {int /*<<< orphan*/  sharpness; int /*<<< orphan*/  whitebal; int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct TYPE_2__ {int no_urb_create; int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {int /*<<< orphan*/  nbalt; TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRIGHTNESS_DEFAULT ; 
 int /*<<< orphan*/  CONTRAST_DEFAULT ; 
 int /*<<< orphan*/  SATURATION_DEFAULT ; 
 int /*<<< orphan*/  SHARPNESS_DEFAULT ; 
 int /*<<< orphan*/  WHITEBAL_DEFAULT ; 
 int /*<<< orphan*/  vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;

	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(vga_mode);
	gspca_dev->cam.no_urb_create = 1;
	/* The highest alt setting has an isoc packetsize of 0, so we
	   don't want to use it */
	gspca_dev->nbalt--;

	sd->brightness  = BRIGHTNESS_DEFAULT;
	sd->contrast    = CONTRAST_DEFAULT;
	sd->saturation  = SATURATION_DEFAULT;
	sd->whitebal    = WHITEBAL_DEFAULT;
	sd->sharpness   = SHARPNESS_DEFAULT;

	return 0;
}