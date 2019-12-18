#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_querymenu {int id; size_t index; int /*<<< orphan*/  name; scalar_t__ reserved; } ;
struct TYPE_8__ {int /*<<< orphan*/  sensor_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  device_type; } ;
struct TYPE_9__ {TYPE_2__ version; TYPE_1__ pnp_id; } ;
struct camera_data {TYPE_3__ params; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  CPIA2_CID_FLICKER_MODE 130 
#define  CPIA2_CID_FRAMERATE 129 
#define  CPIA2_CID_LIGHTS 128 
 int /*<<< orphan*/  CPIA2_VP_FRAMERATE_15 ; 
 int /*<<< orphan*/  CPIA2_VP_SENSOR_FLAGS_500 ; 
 int /*<<< orphan*/  DEVICE_STV_672 ; 
 int EINVAL ; 
 size_t NUM_FLICKER_CONTROLS ; 
 int /*<<< orphan*/  NUM_FRAMERATE_CONTROLS ; 
 size_t NUM_LIGHTS_CONTROLS ; 
 TYPE_6__* flicker_controls ; 
 TYPE_5__* framerate_controls ; 
 TYPE_4__* lights_controls ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_querymenu(void *arg,struct camera_data *cam)
{
	struct v4l2_querymenu *m = arg;

	memset(m->name, 0, sizeof(m->name));
	m->reserved = 0;

	switch(m->id) {
	case CPIA2_CID_FLICKER_MODE:
		if (m->index >= NUM_FLICKER_CONTROLS)
			return -EINVAL;

		strcpy(m->name, flicker_controls[m->index].name);
		break;
	case CPIA2_CID_FRAMERATE:
	    {
		int maximum = NUM_FRAMERATE_CONTROLS - 1;
		if(cam->params.pnp_id.device_type == DEVICE_STV_672 &&
		   cam->params.version.sensor_flags==CPIA2_VP_SENSOR_FLAGS_500){
			// Maximum 15fps
			int i;
			for(i=0; i<maximum; ++i) {
				if(framerate_controls[i].value ==
				   CPIA2_VP_FRAMERATE_15)
					maximum = i;
			}
		}
		if (m->index > maximum)
			return -EINVAL;

		strcpy(m->name, framerate_controls[m->index].name);
		break;
	    }
	case CPIA2_CID_LIGHTS:
		if (m->index >= NUM_LIGHTS_CONTROLS)
			return -EINVAL;

		strcpy(m->name, lights_controls[m->index].name);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}