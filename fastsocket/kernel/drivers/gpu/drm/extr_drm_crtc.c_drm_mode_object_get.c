#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_mode_object {int id; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  idr_mutex; int /*<<< orphan*/  crtc_idr; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct drm_mode_object*,int,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_mode_object_get(struct drm_device *dev,
			       struct drm_mode_object *obj, uint32_t obj_type)
{
	int new_id = 0;
	int ret;

again:
	if (idr_pre_get(&dev->mode_config.crtc_idr, GFP_KERNEL) == 0) {
		DRM_ERROR("Ran out memory getting a mode number\n");
		return -ENOMEM;
	}

	mutex_lock(&dev->mode_config.idr_mutex);
	ret = idr_get_new_above(&dev->mode_config.crtc_idr, obj, 1, &new_id);
	mutex_unlock(&dev->mode_config.idr_mutex);
	if (ret == -EAGAIN)
		goto again;
	else if (ret)
		return ret;

	obj->id = new_id;
	obj->type = obj_type;
	return 0;
}