#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_13__ {scalar_t__ clipcount; scalar_t__ flags; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_22__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_21__ {scalar_t__ contrast; scalar_t__ saturation; scalar_t__ brightness; } ;
struct TYPE_19__ {scalar_t__ sensor_flags; } ;
struct TYPE_18__ {void* frame_rate; scalar_t__ gpio_data; scalar_t__ gpio_direction; scalar_t__ lowlight_boost; } ;
struct TYPE_17__ {scalar_t__ device_type; } ;
struct TYPE_16__ {int /*<<< orphan*/  target_kb; } ;
struct TYPE_15__ {int creep_period; int user_squeeze; int inhibit_htables; int /*<<< orphan*/  jpeg_options; } ;
struct TYPE_14__ {int mains_frequency; int /*<<< orphan*/  flicker_mode_req; } ;
struct TYPE_12__ {TYPE_9__ roi; TYPE_8__ color_params; TYPE_6__ version; TYPE_5__ vp_params; TYPE_4__ pnp_id; TYPE_3__ vc_params; TYPE_2__ compression; TYPE_1__ flicker_control; } ;
struct TYPE_20__ {int palette; int brightness; int colour; int contrast; } ;
struct camera_data {TYPE_11__ vw; TYPE_10__ params; TYPE_7__ vp; int /*<<< orphan*/  video_size; int /*<<< orphan*/  sensor_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_SENSOR_410 ; 
 int /*<<< orphan*/  CPIA2_SENSOR_500 ; 
 int /*<<< orphan*/  CPIA2_VC_VC_JPEG_OPT_DEFAULT ; 
 void* CPIA2_VP_FRAMERATE_15 ; 
 void* CPIA2_VP_FRAMERATE_30 ; 
 scalar_t__ CPIA2_VP_SENSOR_FLAGS_500 ; 
 scalar_t__ DEFAULT_BRIGHTNESS ; 
 scalar_t__ DEFAULT_CONTRAST ; 
 scalar_t__ DEFAULT_SATURATION ; 
 int /*<<< orphan*/  DEFAULT_TARGET_KB ; 
 scalar_t__ DEVICE_STV_672 ; 
 int /*<<< orphan*/  NEVER_FLICKER ; 
 int /*<<< orphan*/  STV_IMAGE_CIF_COLS ; 
 int /*<<< orphan*/  STV_IMAGE_CIF_ROWS ; 
 int /*<<< orphan*/  STV_IMAGE_VGA_COLS ; 
 int /*<<< orphan*/  STV_IMAGE_VGA_ROWS ; 
 int /*<<< orphan*/  VIDEOSIZE_CIF ; 
 int /*<<< orphan*/  VIDEOSIZE_VGA ; 
 scalar_t__ VIDEO_PALETTE_RGB24 ; 

__attribute__((used)) static void reset_camera_struct(struct camera_data *cam)
{
	/***
	 * The following parameter values are the defaults from the register map.
	 ***/
	cam->params.color_params.brightness = DEFAULT_BRIGHTNESS;
	cam->params.color_params.contrast = DEFAULT_CONTRAST;
	cam->params.color_params.saturation = DEFAULT_SATURATION;
	cam->params.vp_params.lowlight_boost = 0;

	/* FlickerModes */
	cam->params.flicker_control.flicker_mode_req = NEVER_FLICKER;
	cam->params.flicker_control.mains_frequency = 60;

	/* jpeg params */
	cam->params.compression.jpeg_options = CPIA2_VC_VC_JPEG_OPT_DEFAULT;
	cam->params.compression.creep_period = 2;
	cam->params.compression.user_squeeze = 20;
	cam->params.compression.inhibit_htables = false;

	/* gpio params */
	cam->params.vp_params.gpio_direction = 0;	/* write, the default safe mode */
	cam->params.vp_params.gpio_data = 0;

	/* Target kb params */
	cam->params.vc_params.target_kb = DEFAULT_TARGET_KB;

	/***
	 * Set Sensor FPS as fast as possible.
	 ***/
	if(cam->params.pnp_id.device_type == DEVICE_STV_672) {
		if(cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500)
			cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_15;
		else
			cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_30;
	} else {
		cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_30;
	}

	/***
	 * Set default video mode as large as possible :
	 * for vga sensor set to vga, for cif sensor set to CIF.
	 ***/
	if (cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500) {
		cam->sensor_type = CPIA2_SENSOR_500;
		cam->video_size = VIDEOSIZE_VGA;
		cam->params.roi.width = STV_IMAGE_VGA_COLS;
		cam->params.roi.height = STV_IMAGE_VGA_ROWS;
	} else {
		cam->sensor_type = CPIA2_SENSOR_410;
		cam->video_size = VIDEOSIZE_CIF;
		cam->params.roi.width = STV_IMAGE_CIF_COLS;
		cam->params.roi.height = STV_IMAGE_CIF_ROWS;
	}

	/***
	 * Fill in the v4l structures.  video_cap is filled in inside the VIDIOCCAP
	 * Ioctl.  Here, just do the window and picture stucts.
	 ***/
	cam->vp.palette = (u16) VIDEO_PALETTE_RGB24;	/* Is this right? */
	cam->vp.brightness = (u16) cam->params.color_params.brightness * 256;
	cam->vp.colour = (u16) cam->params.color_params.saturation * 256;
	cam->vp.contrast = (u16) cam->params.color_params.contrast * 256;

	cam->vw.x = 0;
	cam->vw.y = 0;
	cam->vw.width = cam->params.roi.width;
	cam->vw.height = cam->params.roi.height;
	cam->vw.flags = 0;
	cam->vw.clipcount = 0;

	return;
}