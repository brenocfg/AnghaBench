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
typedef  int u32 ;
struct v4l2_ext_control {int value; int /*<<< orphan*/  id; } ;
struct uvc_video_chain {TYPE_4__* dev; } ;
struct uvc_control_mapping {int v4l2_type; int (* get ) (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int menu_count; int size; int /*<<< orphan*/  (* set ) (struct uvc_control_mapping*,int,int /*<<< orphan*/ ) ;TYPE_1__* menu_info; } ;
struct TYPE_7__ {int flags; int size; int /*<<< orphan*/  selector; } ;
struct uvc_control {int loaded; int dirty; int modified; TYPE_3__ info; TYPE_2__* entity; int /*<<< orphan*/  cached; } ;
typedef  int s32 ;
struct TYPE_8__ {int /*<<< orphan*/  intfnum; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int UVC_CONTROL_GET_CUR ; 
 int UVC_CONTROL_SET_CUR ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_BACKUP ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_CURRENT ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_MAX ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_MIN ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_RES ; 
 int /*<<< orphan*/  UVC_GET_CUR ; 
 int /*<<< orphan*/  UVC_GET_MAX ; 
 int /*<<< orphan*/  UVC_GET_MIN ; 
 int /*<<< orphan*/  UVC_GET_RES ; 
#define  V4L2_CTRL_TYPE_BOOLEAN 130 
#define  V4L2_CTRL_TYPE_INTEGER 129 
#define  V4L2_CTRL_TYPE_MENU 128 
 void* clamp (int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct uvc_control_mapping*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_ctrl_data (struct uvc_control*,int /*<<< orphan*/ ) ; 
 int uvc_ctrl_populate_cache (struct uvc_video_chain*,struct uvc_control*) ; 
 struct uvc_control* uvc_find_control (struct uvc_video_chain*,int /*<<< orphan*/ ,struct uvc_control_mapping**) ; 
 int uvc_query_ctrl (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int uvc_ctrl_set(struct uvc_video_chain *chain,
	struct v4l2_ext_control *xctrl)
{
	struct uvc_control *ctrl;
	struct uvc_control_mapping *mapping;
	s32 value;
	u32 step;
	s32 min;
	s32 max;
	int ret;

	ctrl = uvc_find_control(chain, xctrl->id, &mapping);
	if (ctrl == NULL || (ctrl->info.flags & UVC_CONTROL_SET_CUR) == 0)
		return -EINVAL;

	/* Clamp out of range values. */
	switch (mapping->v4l2_type) {
	case V4L2_CTRL_TYPE_INTEGER:
		if (!ctrl->cached) {
			ret = uvc_ctrl_populate_cache(chain, ctrl);
			if (ret < 0)
				return ret;
		}

		min = mapping->get(mapping, UVC_GET_MIN,
				   uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MIN));
		max = mapping->get(mapping, UVC_GET_MAX,
				   uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MAX));
		step = mapping->get(mapping, UVC_GET_RES,
				    uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES));
		if (step == 0)
			step = 1;

		xctrl->value = min + (xctrl->value - min + step/2) / step * step;
		xctrl->value = clamp(xctrl->value, min, max);
		value = xctrl->value;
		break;

	case V4L2_CTRL_TYPE_BOOLEAN:
		xctrl->value = clamp(xctrl->value, 0, 1);
		value = xctrl->value;
		break;

	case V4L2_CTRL_TYPE_MENU:
		if (xctrl->value < 0 || xctrl->value >= mapping->menu_count)
			return -ERANGE;
		value = mapping->menu_info[xctrl->value].value;
		break;

	default:
		value = xctrl->value;
		break;
	}

	/* If the mapping doesn't span the whole UVC control, the current value
	 * needs to be loaded from the device to perform the read-modify-write
	 * operation.
	 */
	if (!ctrl->loaded && (ctrl->info.size * 8) != mapping->size) {
		if ((ctrl->info.flags & UVC_CONTROL_GET_CUR) == 0) {
			memset(uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
				0, ctrl->info.size);
		} else {
			ret = uvc_query_ctrl(chain->dev, UVC_GET_CUR,
				ctrl->entity->id, chain->dev->intfnum,
				ctrl->info.selector,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
				ctrl->info.size);
			if (ret < 0)
				return ret;
		}

		ctrl->loaded = 1;
	}

	/* Backup the current value in case we need to rollback later. */
	if (!ctrl->dirty) {
		memcpy(uvc_ctrl_data(ctrl, UVC_CTRL_DATA_BACKUP),
		       uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
		       ctrl->info.size);
	}

	mapping->set(mapping, value,
		uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT));

	ctrl->dirty = 1;
	ctrl->modified = 1;
	return 0;
}