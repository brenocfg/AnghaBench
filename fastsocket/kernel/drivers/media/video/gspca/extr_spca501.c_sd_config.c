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
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct sd {int /*<<< orphan*/  colors; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; int /*<<< orphan*/  subtype; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;
struct TYPE_3__ {int /*<<< orphan*/  default_value; } ;
struct TYPE_4__ {TYPE_1__ qctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t MY_BRIGHTNESS ; 
 size_t MY_COLOR ; 
 size_t MY_CONTRAST ; 
 TYPE_2__* sd_ctrls ; 
 int /*<<< orphan*/  vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);
	sd->subtype = id->driver_info;
	sd->brightness = sd_ctrls[MY_BRIGHTNESS].qctrl.default_value;
	sd->contrast = sd_ctrls[MY_CONTRAST].qctrl.default_value;
	sd->colors = sd_ctrls[MY_COLOR].qctrl.default_value;

	return 0;
}