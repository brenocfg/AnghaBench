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
struct usb_device_id {int idVendor; int idProduct; scalar_t__ driver_info; } ;
struct sd {scalar_t__ chip_revision; int /*<<< orphan*/  expo12a; int /*<<< orphan*/  gain; int /*<<< orphan*/  autogain; int /*<<< orphan*/  exposure; int /*<<< orphan*/  white; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct cam {void* nmodes; void* cam_mode; } ;
struct gspca_dev {int* usb_buf; int nbalt; struct cam cam; } ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  AUTOGAIN_DEF ; 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  CONTRAST_DEF ; 
 int /*<<< orphan*/  D_PROBE ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXPO12A_DEF ; 
 int /*<<< orphan*/  EXPOSURE_DEF ; 
 int /*<<< orphan*/  GAIN_DEF ; 
 int /*<<< orphan*/  HUE_DEF ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ Rev012A ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 void* sif_012a_mode ; 
 void* sif_072a_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;
	__u16 vendor, product;
	__u8 data1, data2;

	/* Read frm global register the USB product and vendor IDs, just to
	 * prove that we can communicate with the device.  This works, which
	 * confirms at we are communicating properly and that the device
	 * is a 561. */
	reg_r(gspca_dev, 0x8104, 1);
	data1 = gspca_dev->usb_buf[0];
	reg_r(gspca_dev, 0x8105, 1);
	data2 = gspca_dev->usb_buf[0];
	vendor = (data2 << 8) | data1;
	reg_r(gspca_dev, 0x8106, 1);
	data1 = gspca_dev->usb_buf[0];
	reg_r(gspca_dev, 0x8107, 1);
	data2 = gspca_dev->usb_buf[0];
	product = (data2 << 8) | data1;
	if (vendor != id->idVendor || product != id->idProduct) {
		PDEBUG(D_PROBE, "Bad vendor / product from device");
		return -EINVAL;
	}

	cam = &gspca_dev->cam;
	gspca_dev->nbalt = 7 + 1;	/* choose alternate 7 first */

	sd->chip_revision = id->driver_info;
	if (sd->chip_revision == Rev012A) {
		cam->cam_mode = sif_012a_mode;
		cam->nmodes = ARRAY_SIZE(sif_012a_mode);
	} else {
		cam->cam_mode = sif_072a_mode;
		cam->nmodes = ARRAY_SIZE(sif_072a_mode);
	}
	sd->brightness = BRIGHTNESS_DEF;
	sd->contrast = CONTRAST_DEF;
	sd->white = HUE_DEF;
	sd->exposure = EXPOSURE_DEF;
	sd->autogain = AUTOGAIN_DEF;
	sd->gain = GAIN_DEF;
	sd->expo12a = EXPO12A_DEF;
	return 0;
}