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
struct uvc_device {TYPE_1__* udev; } ;
struct uvc_control_info {int dummy; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  selector; int /*<<< orphan*/  entity; int /*<<< orphan*/  mappings; } ;
struct uvc_control {int initialized; int /*<<< orphan*/ * uvc_data; TYPE_2__* entity; TYPE_3__ info; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  devpath; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int UVC_CTRL_DATA_LAST ; 
 int /*<<< orphan*/  UVC_TRACE_CONTROL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct uvc_control_info const*,int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvc_ctrl_add_info(struct uvc_device *dev, struct uvc_control *ctrl,
	const struct uvc_control_info *info)
{
	int ret = 0;

	memcpy(&ctrl->info, info, sizeof(*info));
	INIT_LIST_HEAD(&ctrl->info.mappings);

	/* Allocate an array to save control values (cur, def, max, etc.) */
	ctrl->uvc_data = kzalloc(ctrl->info.size * UVC_CTRL_DATA_LAST + 1,
				 GFP_KERNEL);
	if (ctrl->uvc_data == NULL) {
		ret = -ENOMEM;
		goto done;
	}

	ctrl->initialized = 1;

	uvc_trace(UVC_TRACE_CONTROL, "Added control %pUl/%u to device %s "
		"entity %u\n", ctrl->info.entity, ctrl->info.selector,
		dev->udev->devpath, ctrl->entity->id);

done:
	if (ret < 0)
		kfree(ctrl->uvc_data);
	return ret;
}