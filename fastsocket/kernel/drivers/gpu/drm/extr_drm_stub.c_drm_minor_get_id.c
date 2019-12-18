#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_MINOR_CONTROL ; 
 int DRM_MINOR_RENDER ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_minors_idr ; 
 int idr_get_new_above (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_minor_get_id(struct drm_device *dev, int type)
{
	int new_id;
	int ret;
	int base = 0, limit = 63;

	if (type == DRM_MINOR_CONTROL) {
                base += 64;
                limit = base + 127;
        } else if (type == DRM_MINOR_RENDER) {
                base += 128;
                limit = base + 255;
        }

again:
	if (idr_pre_get(&drm_minors_idr, GFP_KERNEL) == 0) {
		DRM_ERROR("Out of memory expanding drawable idr\n");
		return -ENOMEM;
	}
	mutex_lock(&dev->struct_mutex);
	ret = idr_get_new_above(&drm_minors_idr, NULL,
				base, &new_id);
	mutex_unlock(&dev->struct_mutex);
	if (ret == -EAGAIN)
		goto again;
	else if (ret)
		return ret;

	if (new_id >= limit) {
		idr_remove(&drm_minors_idr, new_id);
		return -EINVAL;
	}
	return new_id;
}