#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct drm_i915_master_private {scalar_t__ sarea_priv; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_2__* primary; scalar_t__ dev_private; } ;
struct drm_clip_rect {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  last_dispatch; } ;
typedef  TYPE_4__ drm_i915_sarea_t ;
struct TYPE_11__ {int /*<<< orphan*/  allow_batchbuffer; } ;
struct TYPE_13__ {TYPE_3__ dri1; } ;
typedef  TYPE_5__ drm_i915_private_t ;
struct TYPE_14__ {int num_cliprects; int /*<<< orphan*/  cliprects; int /*<<< orphan*/  used; int /*<<< orphan*/  start; } ;
typedef  TYPE_6__ drm_i915_batchbuffer_t ;
struct TYPE_10__ {TYPE_1__* master; } ;
struct TYPE_9__ {struct drm_i915_master_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  READ_BREADCRUMB (TYPE_5__*) ; 
 int /*<<< orphan*/  RING_LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int copy_from_user (struct drm_clip_rect*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int i915_dispatch_batchbuffer (struct drm_device*,TYPE_6__*,struct drm_clip_rect*) ; 
 struct drm_clip_rect* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_clip_rect*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_batchbuffer(struct drm_device *dev, void *data,
			    struct drm_file *file_priv)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;
	drm_i915_sarea_t *sarea_priv = (drm_i915_sarea_t *)
	    master_priv->sarea_priv;
	drm_i915_batchbuffer_t *batch = data;
	int ret;
	struct drm_clip_rect *cliprects = NULL;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	if (!dev_priv->dri1.allow_batchbuffer) {
		DRM_ERROR("Batchbuffer ioctl disabled\n");
		return -EINVAL;
	}

	DRM_DEBUG_DRIVER("i915 batchbuffer, start %x used %d cliprects %d\n",
			batch->start, batch->used, batch->num_cliprects);

	RING_LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (batch->num_cliprects < 0)
		return -EINVAL;

	if (batch->num_cliprects) {
		cliprects = kcalloc(batch->num_cliprects,
				    sizeof(struct drm_clip_rect),
				    GFP_KERNEL);
		if (cliprects == NULL)
			return -ENOMEM;

		ret = copy_from_user(cliprects, batch->cliprects,
				     batch->num_cliprects *
				     sizeof(struct drm_clip_rect));
		if (ret != 0) {
			ret = -EFAULT;
			goto fail_free;
		}
	}

	mutex_lock(&dev->struct_mutex);
	ret = i915_dispatch_batchbuffer(dev, batch, cliprects);
	mutex_unlock(&dev->struct_mutex);

	if (sarea_priv)
		sarea_priv->last_dispatch = READ_BREADCRUMB(dev_priv);

fail_free:
	kfree(cliprects);

	return ret;
}