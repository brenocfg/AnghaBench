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
struct sd {scalar_t__ cam_type; scalar_t__ sof_read; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAM_TYPE_CIF ; 
 int isoc_enable (struct gspca_dev*) ; 
 int /*<<< orphan*/  setbrightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcontrast (struct gspca_dev*) ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*) ; 
 int /*<<< orphan*/  setgain (struct gspca_dev*) ; 
 int start_cif_cam (struct gspca_dev*) ; 
 int start_vga_cam (struct gspca_dev*) ; 
 int stream_start (struct gspca_dev*) ; 
 int zero_the_pointer (struct gspca_dev*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int err_code;

	sd->sof_read = 0;

	/* Some of the VGA cameras require the memory pointer
	 * to be set to 0 again. We have been forced to start the
	 * stream in sd_config() to detect the hardware, and closed it.
	 * Thus, we need here to do a completely fresh and clean start. */
	err_code = zero_the_pointer(gspca_dev);
	if (err_code < 0)
		return err_code;

	err_code = stream_start(gspca_dev);
	if (err_code < 0)
		return err_code;

	if (sd->cam_type == CAM_TYPE_CIF) {
		err_code = start_cif_cam(gspca_dev);
	} else {
		err_code = start_vga_cam(gspca_dev);
	}
	if (err_code < 0)
		return err_code;

	setbrightness(gspca_dev);
	setcontrast(gspca_dev);
	setexposure(gspca_dev);
	setgain(gspca_dev);

	return isoc_enable(gspca_dev);
}