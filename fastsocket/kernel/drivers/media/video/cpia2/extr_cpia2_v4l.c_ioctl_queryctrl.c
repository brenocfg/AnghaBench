#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_queryctrl {int id; int minimum; int maximum; int default_value; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int product; int /*<<< orphan*/  device_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  sensor_flags; } ;
struct TYPE_9__ {TYPE_2__ pnp_id; TYPE_1__ version; } ;
struct camera_data {TYPE_3__ params; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct TYPE_10__ {int id; } ;

/* Variables and functions */
#define  CPIA2_CID_FLICKER_MODE 132 
#define  CPIA2_CID_FRAMERATE 131 
#define  CPIA2_CID_LIGHTS 130 
 int /*<<< orphan*/  CPIA2_VP_FRAMERATE_15 ; 
 int /*<<< orphan*/  CPIA2_VP_SENSOR_FLAGS_500 ; 
 int /*<<< orphan*/  DEVICE_STV_672 ; 
 int EINVAL ; 
 int NUM_CONTROLS ; 
#define  V4L2_CID_BRIGHTNESS 129 
#define  V4L2_CID_VFLIP 128 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_DISABLED ; 
 TYPE_4__* controls ; 
 TYPE_5__* framerate_controls ; 
 int /*<<< orphan*/  memcpy (struct v4l2_queryctrl*,TYPE_4__*,int) ; 

__attribute__((used)) static int ioctl_queryctrl(void *arg,struct camera_data *cam)
{
	struct v4l2_queryctrl *c = arg;
	int i;

	for(i=0; i<NUM_CONTROLS; ++i) {
		if(c->id == controls[i].id) {
			memcpy(c, controls+i, sizeof(*c));
			break;
		}
	}

	if(i == NUM_CONTROLS)
		return -EINVAL;

	/* Some devices have additional limitations */
	switch(c->id) {
	case V4L2_CID_BRIGHTNESS:
		/***
		 * Don't let the register be set to zero - bug in VP4
		 * flash of full brightness
		 ***/
		if (cam->params.pnp_id.device_type == DEVICE_STV_672)
			c->minimum = 1;
		break;
	case V4L2_CID_VFLIP:
		// VP5 Only
		if(cam->params.pnp_id.device_type == DEVICE_STV_672)
			c->flags |= V4L2_CTRL_FLAG_DISABLED;
		break;
	case CPIA2_CID_FRAMERATE:
		if(cam->params.pnp_id.device_type == DEVICE_STV_672 &&
		   cam->params.version.sensor_flags==CPIA2_VP_SENSOR_FLAGS_500){
			// Maximum 15fps
			for(i=0; i<c->maximum; ++i) {
				if(framerate_controls[i].value ==
				   CPIA2_VP_FRAMERATE_15) {
					c->maximum = i;
					c->default_value = i;
				}
			}
		}
		break;
	case CPIA2_CID_FLICKER_MODE:
		// Flicker control only valid for 672.
		if(cam->params.pnp_id.device_type != DEVICE_STV_672)
			c->flags |= V4L2_CTRL_FLAG_DISABLED;
		break;
	case CPIA2_CID_LIGHTS:
		// Light control only valid for the QX5 Microscope.
		if(cam->params.pnp_id.product != 0x151)
			c->flags |= V4L2_CTRL_FLAG_DISABLED;
		break;
	default:
		break;
	}

	return 0;
}