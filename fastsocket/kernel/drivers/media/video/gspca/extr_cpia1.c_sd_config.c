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
struct usb_device_id {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  FREQ_DEF ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode ; 
 int /*<<< orphan*/  reset_camera_params (struct gspca_dev*) ; 
 int /*<<< orphan*/  sd_setfreq (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct cam *cam;

	reset_camera_params(gspca_dev);

	PDEBUG(D_PROBE, "cpia CPiA camera detected (vid/pid 0x%04X:0x%04X)",
	       id->idVendor, id->idProduct);

	cam = &gspca_dev->cam;
	cam->cam_mode = mode;
	cam->nmodes = ARRAY_SIZE(mode);

	sd_setfreq(gspca_dev, FREQ_DEF);

	return 0;
}