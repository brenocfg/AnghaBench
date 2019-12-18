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
struct file {struct drm_file* private_data; } ;
struct drm_file {TYPE_1__* master; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* hw_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_3__ lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _DRM_LOCKING_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_i_have_hw_lock (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  drm_lock_free (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drm_master_release(struct drm_device *dev, struct file *filp)
{
	struct drm_file *file_priv = filp->private_data;

	if (drm_i_have_hw_lock(dev, file_priv)) {
		DRM_DEBUG("File %p released, freeing lock for context %d\n",
			  filp, _DRM_LOCKING_CONTEXT(file_priv->master->lock.hw_lock->lock));
		drm_lock_free(&file_priv->master->lock,
			      _DRM_LOCKING_CONTEXT(file_priv->master->lock.hw_lock->lock));
	}
}