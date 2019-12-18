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
struct video_capability {int type; int channels; int minwidth; int minheight; int /*<<< orphan*/  maxheight; int /*<<< orphan*/  maxwidth; scalar_t__ audios; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int sensor_flags; } ;
struct TYPE_4__ {int product; } ;
struct TYPE_6__ {TYPE_2__ version; TYPE_1__ pnp_id; } ;
struct camera_data {TYPE_3__ params; } ;

/* Variables and functions */
#define  CPIA2_VP_SENSOR_FLAGS_410 129 
#define  CPIA2_VP_SENSOR_FLAGS_500 128 
 int EINVAL ; 
 int /*<<< orphan*/  STV_IMAGE_CIF_COLS ; 
 int /*<<< orphan*/  STV_IMAGE_CIF_ROWS ; 
 int /*<<< orphan*/  STV_IMAGE_VGA_COLS ; 
 int /*<<< orphan*/  STV_IMAGE_VGA_ROWS ; 
 int VID_TYPE_CAPTURE ; 
 int VID_TYPE_MJPEG_ENCODER ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ioctl_cap_query(void *arg, struct camera_data *cam)
{
	struct video_capability *vc;
	int retval = 0;
	vc = arg;

	if (cam->params.pnp_id.product == 0x151)
		strcpy(vc->name, "QX5 Microscope");
	else
		strcpy(vc->name, "CPiA2 Camera");

	vc->type = VID_TYPE_CAPTURE | VID_TYPE_MJPEG_ENCODER;
	vc->channels = 1;
	vc->audios = 0;
	vc->minwidth = 176;	/* VIDEOSIZE_QCIF */
	vc->minheight = 144;
	switch (cam->params.version.sensor_flags) {
	case CPIA2_VP_SENSOR_FLAGS_500:
		vc->maxwidth = STV_IMAGE_VGA_COLS;
		vc->maxheight = STV_IMAGE_VGA_ROWS;
		break;
	case CPIA2_VP_SENSOR_FLAGS_410:
		vc->maxwidth = STV_IMAGE_CIF_COLS;
		vc->maxheight = STV_IMAGE_CIF_ROWS;
		break;
	default:
		return -EINVAL;
	}

	return retval;
}