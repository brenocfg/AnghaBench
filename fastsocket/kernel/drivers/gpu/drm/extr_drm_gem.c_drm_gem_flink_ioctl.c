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
typedef  void* uint64_t ;
struct drm_gem_object {scalar_t__ name; } ;
struct drm_gem_flink {void* name; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  object_name_lock; int /*<<< orphan*/  object_name_idr; TYPE_1__* driver; } ;
struct TYPE_2__ {int driver_features; } ;

/* Variables and functions */
 int DRIVER_GEM ; 
 int EAGAIN ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_reference (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct drm_gem_object*,int,scalar_t__*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
drm_gem_flink_ioctl(struct drm_device *dev, void *data,
		    struct drm_file *file_priv)
{
	struct drm_gem_flink *args = data;
	struct drm_gem_object *obj;
	int ret;

	if (!(dev->driver->driver_features & DRIVER_GEM))
		return -ENODEV;

	obj = drm_gem_object_lookup(dev, file_priv, args->handle);
	if (obj == NULL)
		return -ENOENT;

again:
	if (idr_pre_get(&dev->object_name_idr, GFP_KERNEL) == 0) {
		ret = -ENOMEM;
		goto err;
	}

	spin_lock(&dev->object_name_lock);
	if (!obj->name) {
		ret = idr_get_new_above(&dev->object_name_idr, obj, 1,
					&obj->name);
		args->name = (uint64_t) obj->name;
		spin_unlock(&dev->object_name_lock);

		if (ret == -EAGAIN)
			goto again;
		else if (ret)
			goto err;

		/* Allocate a reference for the name table.  */
		drm_gem_object_reference(obj);
	} else {
		args->name = (uint64_t) obj->name;
		spin_unlock(&dev->object_name_lock);
		ret = 0;
	}

err:
	drm_gem_object_unreference_unlocked(obj);
	return ret;
}