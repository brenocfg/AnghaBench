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
struct usb_device_id {int driver_info; } ;
struct sd {int model; int sof_len; int stop_on_control_change; int /*<<< orphan*/  hflip; int /*<<< orphan*/  lighting; int /*<<< orphan*/  sharpness; int /*<<< orphan*/  hue; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct cam {int nmodes; int reverse_alts; int /*<<< orphan*/  input_flags; void* cam_mode; } ;
struct gspca_dev {int ctrl_dis; struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  BRIGHTNESS_DEFAULT ; 
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int /*<<< orphan*/  CONTRAST_DEFAULT ; 
 int /*<<< orphan*/  HFLIP_DEFAULT ; 
 int /*<<< orphan*/  HUE_DEFAULT ; 
 int /*<<< orphan*/  LIGHTING_DEFAULT ; 
 int SD_CONTRAST ; 
 int SD_HFLIP ; 
 int SD_HUE ; 
 int SD_LIGHTING ; 
 int SD_SHARPNESS ; 
 int /*<<< orphan*/  SHARPNESS_DEFAULT ; 
 int /*<<< orphan*/  V4L2_IN_ST_VFLIP ; 
 void* cif_yuv_mode ; 
 scalar_t__ ibm_netcam_pro ; 
 void* model0_mode ; 
 void* model2_mode ; 
 void* vga_yuv_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	sd->model = id->driver_info;
	if (sd->model == CIT_MODEL3 && ibm_netcam_pro)
		sd->model = CIT_IBM_NETCAM_PRO;

	cam = &gspca_dev->cam;
	switch (sd->model) {
	case CIT_MODEL0:
		cam->cam_mode = model0_mode;
		cam->nmodes = ARRAY_SIZE(model0_mode);
		cam->reverse_alts = 1;
		gspca_dev->ctrl_dis = ~((1 << SD_CONTRAST) | (1 << SD_HFLIP));
		sd->sof_len = 4;
		break;
	case CIT_MODEL1:
		cam->cam_mode = cif_yuv_mode;
		cam->nmodes = ARRAY_SIZE(cif_yuv_mode);
		cam->reverse_alts = 1;
		gspca_dev->ctrl_dis = (1 << SD_HUE) | (1 << SD_HFLIP);
		sd->sof_len = 4;
		break;
	case CIT_MODEL2:
		cam->cam_mode = model2_mode + 1; /* no 160x120 */
		cam->nmodes = 3;
		gspca_dev->ctrl_dis = (1 << SD_CONTRAST) |
				      (1 << SD_SHARPNESS) |
				      (1 << SD_HFLIP);
		break;
	case CIT_MODEL3:
		cam->cam_mode = vga_yuv_mode;
		cam->nmodes = ARRAY_SIZE(vga_yuv_mode);
		gspca_dev->ctrl_dis = (1 << SD_HUE) |
				      (1 << SD_LIGHTING) |
				      (1 << SD_HFLIP);
		sd->stop_on_control_change = 1;
		sd->sof_len = 4;
		break;
	case CIT_MODEL4:
		cam->cam_mode = model2_mode;
		cam->nmodes = ARRAY_SIZE(model2_mode);
		gspca_dev->ctrl_dis = (1 << SD_CONTRAST) |
				      (1 << SD_SHARPNESS) |
				      (1 << SD_LIGHTING) |
				      (1 << SD_HFLIP);
		break;
	case CIT_IBM_NETCAM_PRO:
		cam->cam_mode = vga_yuv_mode;
		cam->nmodes = 2; /* no 640 x 480 */
		cam->input_flags = V4L2_IN_ST_VFLIP;
		gspca_dev->ctrl_dis = ~(1 << SD_CONTRAST);
		sd->stop_on_control_change = 1;
		sd->sof_len = 4;
		break;
	}

	sd->brightness = BRIGHTNESS_DEFAULT;
	sd->contrast = CONTRAST_DEFAULT;
	sd->hue = HUE_DEFAULT;
	sd->sharpness = SHARPNESS_DEFAULT;
	sd->lighting = LIGHTING_DEFAULT;
	sd->hflip = HFLIP_DEFAULT;

	return 0;
}