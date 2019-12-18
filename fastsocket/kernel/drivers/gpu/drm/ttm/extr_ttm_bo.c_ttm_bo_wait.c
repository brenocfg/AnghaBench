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
struct ttm_buffer_object {void* sync_obj; int /*<<< orphan*/  priv_flags; struct ttm_bo_device* bdev; } ;
struct ttm_bo_driver {int (* sync_obj_wait ) (void*,int,int) ;int /*<<< orphan*/  (* sync_obj_unref ) (void**) ;void* (* sync_obj_ref ) (void*) ;scalar_t__ (* sync_obj_signaled ) (void*) ;} ;
struct ttm_bo_device {int /*<<< orphan*/  fence_lock; struct ttm_bo_driver* driver; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TTM_BO_PRIV_FLAG_MOVING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void**) ; 
 void* stub3 (void*) ; 
 int stub4 (void*,int,int) ; 
 int /*<<< orphan*/  stub5 (void**) ; 
 int /*<<< orphan*/  stub6 (void**) ; 
 int /*<<< orphan*/  stub7 (void**) ; 
 int /*<<< orphan*/  stub8 (void**) ; 
 scalar_t__ unlikely (int) ; 

int ttm_bo_wait(struct ttm_buffer_object *bo,
		bool lazy, bool interruptible, bool no_wait)
{
	struct ttm_bo_driver *driver = bo->bdev->driver;
	struct ttm_bo_device *bdev = bo->bdev;
	void *sync_obj;
	int ret = 0;

	if (likely(bo->sync_obj == NULL))
		return 0;

	while (bo->sync_obj) {

		if (driver->sync_obj_signaled(bo->sync_obj)) {
			void *tmp_obj = bo->sync_obj;
			bo->sync_obj = NULL;
			clear_bit(TTM_BO_PRIV_FLAG_MOVING, &bo->priv_flags);
			spin_unlock(&bdev->fence_lock);
			driver->sync_obj_unref(&tmp_obj);
			spin_lock(&bdev->fence_lock);
			continue;
		}

		if (no_wait)
			return -EBUSY;

		sync_obj = driver->sync_obj_ref(bo->sync_obj);
		spin_unlock(&bdev->fence_lock);
		ret = driver->sync_obj_wait(sync_obj,
					    lazy, interruptible);
		if (unlikely(ret != 0)) {
			driver->sync_obj_unref(&sync_obj);
			spin_lock(&bdev->fence_lock);
			return ret;
		}
		spin_lock(&bdev->fence_lock);
		if (likely(bo->sync_obj == sync_obj)) {
			void *tmp_obj = bo->sync_obj;
			bo->sync_obj = NULL;
			clear_bit(TTM_BO_PRIV_FLAG_MOVING,
				  &bo->priv_flags);
			spin_unlock(&bdev->fence_lock);
			driver->sync_obj_unref(&sync_obj);
			driver->sync_obj_unref(&tmp_obj);
			spin_lock(&bdev->fence_lock);
		} else {
			spin_unlock(&bdev->fence_lock);
			driver->sync_obj_unref(&sync_obj);
			spin_lock(&bdev->fence_lock);
		}
	}
	return 0;
}