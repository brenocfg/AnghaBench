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
struct drm_property {int dummy; } ;
struct drm_mode_object {int type; TYPE_1__* properties; } ;
struct drm_mode_obj_set_property {scalar_t__ obj_id; scalar_t__ prop_id; int /*<<< orphan*/  value; int /*<<< orphan*/  obj_type; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int count; scalar_t__* ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
#define  DRM_MODE_OBJECT_CONNECTOR 130 
#define  DRM_MODE_OBJECT_CRTC 129 
#define  DRM_MODE_OBJECT_PLANE 128 
 int /*<<< orphan*/  DRM_MODE_OBJECT_PROPERTY ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_mode_connector_set_obj_prop (struct drm_mode_object*,struct drm_property*,int /*<<< orphan*/ ) ; 
 int drm_mode_crtc_set_obj_prop (struct drm_mode_object*,struct drm_property*,int /*<<< orphan*/ ) ; 
 struct drm_mode_object* drm_mode_object_find (struct drm_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int drm_mode_plane_set_obj_prop (struct drm_mode_object*,struct drm_property*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_property_change_is_valid (struct drm_property*,int /*<<< orphan*/ ) ; 
 struct drm_property* obj_to_property (struct drm_mode_object*) ; 

int drm_mode_obj_set_property_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file_priv)
{
	struct drm_mode_obj_set_property *arg = data;
	struct drm_mode_object *arg_obj;
	struct drm_mode_object *prop_obj;
	struct drm_property *property;
	int ret = -EINVAL;
	int i;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EINVAL;

	drm_modeset_lock_all(dev);

	arg_obj = drm_mode_object_find(dev, arg->obj_id, arg->obj_type);
	if (!arg_obj)
		goto out;
	if (!arg_obj->properties)
		goto out;

	for (i = 0; i < arg_obj->properties->count; i++)
		if (arg_obj->properties->ids[i] == arg->prop_id)
			break;

	if (i == arg_obj->properties->count)
		goto out;

	prop_obj = drm_mode_object_find(dev, arg->prop_id,
					DRM_MODE_OBJECT_PROPERTY);
	if (!prop_obj)
		goto out;
	property = obj_to_property(prop_obj);

	if (!drm_property_change_is_valid(property, arg->value))
		goto out;

	switch (arg_obj->type) {
	case DRM_MODE_OBJECT_CONNECTOR:
		ret = drm_mode_connector_set_obj_prop(arg_obj, property,
						      arg->value);
		break;
	case DRM_MODE_OBJECT_CRTC:
		ret = drm_mode_crtc_set_obj_prop(arg_obj, property, arg->value);
		break;
	case DRM_MODE_OBJECT_PLANE:
		ret = drm_mode_plane_set_obj_prop(arg_obj, property, arg->value);
		break;
	}

out:
	drm_modeset_unlock_all(dev);
	return ret;
}