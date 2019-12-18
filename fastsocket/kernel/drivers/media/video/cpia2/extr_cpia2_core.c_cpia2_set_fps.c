#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int frame_rate; } ;
struct TYPE_7__ {scalar_t__ device_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  sensor_flags; } ;
struct TYPE_8__ {TYPE_1__ vp_params; TYPE_3__ pnp_id; TYPE_2__ version; } ;
struct camera_data {TYPE_4__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_FRAMERATE_REQ ; 
#define  CPIA2_VP_FRAMERATE_12_5 133 
#define  CPIA2_VP_FRAMERATE_15 132 
#define  CPIA2_VP_FRAMERATE_25 131 
#define  CPIA2_VP_FRAMERATE_30 130 
#define  CPIA2_VP_FRAMERATE_6_25 129 
#define  CPIA2_VP_FRAMERATE_7_5 128 
 int /*<<< orphan*/  CPIA2_VP_SENSOR_FLAGS_500 ; 
 scalar_t__ DEVICE_STV_672 ; 
 int EINVAL ; 
 int /*<<< orphan*/  TRANSFER_WRITE ; 
 int cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int cpia2_set_fps(struct camera_data *cam, int framerate)
{
	int retval;

	switch(framerate) {
		case CPIA2_VP_FRAMERATE_30:
		case CPIA2_VP_FRAMERATE_25:
			if(cam->params.pnp_id.device_type == DEVICE_STV_672 &&
			   cam->params.version.sensor_flags ==
						    CPIA2_VP_SENSOR_FLAGS_500) {
				return -EINVAL;
			}
			/* Fall through */
		case CPIA2_VP_FRAMERATE_15:
		case CPIA2_VP_FRAMERATE_12_5:
		case CPIA2_VP_FRAMERATE_7_5:
		case CPIA2_VP_FRAMERATE_6_25:
			break;
		default:
			return -EINVAL;
	}

	if (cam->params.pnp_id.device_type == DEVICE_STV_672 &&
	    framerate == CPIA2_VP_FRAMERATE_15)
		framerate = 0; /* Work around bug in VP4 */

	retval = cpia2_do_command(cam,
				 CPIA2_CMD_FRAMERATE_REQ,
				 TRANSFER_WRITE,
				 framerate);

	if(retval == 0)
		cam->params.vp_params.frame_rate = framerate;

	return retval;
}