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
struct sd {int quality; int jpegqual; int /*<<< orphan*/  work_struct; } ;
struct cam {int nmodes; int bulk; int bulk_size; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jlj_dostream ; 
 int /*<<< orphan*/  jlj_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		const struct usb_device_id *id)
{
	struct cam *cam = &gspca_dev->cam;
	struct sd *dev  = (struct sd *) gspca_dev;

	dev->quality  = 85;
	dev->jpegqual = 85;
	PDEBUG(D_PROBE,
		"JEILINJ camera detected"
		" (vid/pid 0x%04X:0x%04X)", id->idVendor, id->idProduct);
	cam->cam_mode = jlj_mode;
	cam->nmodes = 1;
	cam->bulk = 1;
	/* We don't use the buffer gspca allocates so make it small. */
	cam->bulk_size = 32;
	INIT_WORK(&dev->work_struct, jlj_dostream);
	return 0;
}