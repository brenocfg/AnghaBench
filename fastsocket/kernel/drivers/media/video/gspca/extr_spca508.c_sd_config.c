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
typedef  int /*<<< orphan*/  u16 ;
struct usb_device_id {size_t driver_info; } ;
struct sd {size_t subtype; int /*<<< orphan*/  brightness; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,...) ; 
 int reg_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sif_mode ; 
#define  spca508_init_data 132 
#define  spca508_sightcam2_init_data 131 
#define  spca508_sightcam_init_data 130 
#define  spca508_vista_init_data 129 
#define  spca508cs110_init_data 128 
 int write_vector (struct gspca_dev*,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;
	int data1, data2;
	const u16 (*init_data)[2];
	static const u16 (*(init_data_tb[]))[2] = {
		spca508_vista_init_data,	/* CreativeVista 0 */
		spca508_sightcam_init_data,	/* HamaUSBSightcam 1 */
		spca508_sightcam2_init_data,	/* HamaUSBSightcam2 2 */
		spca508cs110_init_data,		/* IntelEasyPCCamera 3 */
		spca508cs110_init_data,		/* MicroInnovationIC200 4 */
		spca508_init_data,		/* ViewQuestVQ110 5 */
	};

	/* Read from global register the USB product and vendor IDs, just to
	 * prove that we can communicate with the device.  This works, which
	 * confirms at we are communicating properly and that the device
	 * is a 508. */
	data1 = reg_read(gspca_dev, 0x8104);
	data2 = reg_read(gspca_dev, 0x8105);
	PDEBUG(D_PROBE, "Webcam Vendor ID: 0x%02x%02x", data2, data1);

	data1 = reg_read(gspca_dev, 0x8106);
	data2 = reg_read(gspca_dev, 0x8107);
	PDEBUG(D_PROBE, "Webcam Product ID: 0x%02x%02x", data2, data1);

	data1 = reg_read(gspca_dev, 0x8621);
	PDEBUG(D_PROBE, "Window 1 average luminance: %d", data1);

	cam = &gspca_dev->cam;
	cam->cam_mode = sif_mode;
	cam->nmodes = ARRAY_SIZE(sif_mode);

	sd->subtype = id->driver_info;
	sd->brightness = BRIGHTNESS_DEF;

	init_data = init_data_tb[sd->subtype];
	return write_vector(gspca_dev, init_data);
}