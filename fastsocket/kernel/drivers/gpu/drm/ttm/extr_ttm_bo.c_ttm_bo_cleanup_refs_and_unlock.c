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
struct ttm_buffer_object {int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  reserved; int /*<<< orphan*/  sync_obj; struct ttm_bo_global* glob; struct ttm_bo_device* bdev; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;
struct ttm_bo_driver {int (* sync_obj_wait ) (void*,int,int) ;int /*<<< orphan*/  (* sync_obj_unref ) (void**) ;void* (* sync_obj_ref ) (int /*<<< orphan*/ ) ;} ;
struct ttm_bo_device {int /*<<< orphan*/  fence_lock; struct ttm_bo_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (void*,int,int) ; 
 int /*<<< orphan*/  stub3 (void**) ; 
 int /*<<< orphan*/  ttm_bo_cleanup_memtype_use (struct ttm_buffer_object*) ; 
 int ttm_bo_del_from_lru (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_list_ref_sub (struct ttm_buffer_object*,int,int) ; 
 int ttm_bo_reserve_nolru (struct ttm_buffer_object*,int,int,int,int /*<<< orphan*/ ) ; 
 int ttm_bo_wait (struct ttm_buffer_object*,int,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ttm_bo_cleanup_refs_and_unlock(struct ttm_buffer_object *bo,
					  bool interruptible,
					  bool no_wait_gpu)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_bo_driver *driver = bdev->driver;
	struct ttm_bo_global *glob = bo->glob;
	int put_count;
	int ret;

	spin_lock(&bdev->fence_lock);
	ret = ttm_bo_wait(bo, false, false, true);

	if (ret && !no_wait_gpu) {
		void *sync_obj;

		/*
		 * Take a reference to the fence and unreserve,
		 * at this point the buffer should be dead, so
		 * no new sync objects can be attached.
		 */
		sync_obj = driver->sync_obj_ref(bo->sync_obj);
		spin_unlock(&bdev->fence_lock);

		atomic_set(&bo->reserved, 0);
		wake_up_all(&bo->event_queue);
		spin_unlock(&glob->lru_lock);

		ret = driver->sync_obj_wait(sync_obj, false, interruptible);
		driver->sync_obj_unref(&sync_obj);
		if (ret)
			return ret;

		/*
		 * remove sync_obj with ttm_bo_wait, the wait should be
		 * finished, and no new wait object should have been added.
		 */
		spin_lock(&bdev->fence_lock);
		ret = ttm_bo_wait(bo, false, false, true);
		WARN_ON(ret);
		spin_unlock(&bdev->fence_lock);
		if (ret)
			return ret;

		spin_lock(&glob->lru_lock);
		ret = ttm_bo_reserve_nolru(bo, false, true, false, 0);

		/*
		 * We raced, and lost, someone else holds the reservation now,
		 * and is probably busy in ttm_bo_cleanup_memtype_use.
		 *
		 * Even if it's not the case, because we finished waiting any
		 * delayed destruction would succeed, so just return success
		 * here.
		 */
		if (ret) {
			spin_unlock(&glob->lru_lock);
			return 0;
		}
	} else
		spin_unlock(&bdev->fence_lock);

	if (ret || unlikely(list_empty(&bo->ddestroy))) {
		atomic_set(&bo->reserved, 0);
		wake_up_all(&bo->event_queue);
		spin_unlock(&glob->lru_lock);
		return ret;
	}

	put_count = ttm_bo_del_from_lru(bo);
	list_del_init(&bo->ddestroy);
	++put_count;

	spin_unlock(&glob->lru_lock);
	ttm_bo_cleanup_memtype_use(bo);

	ttm_bo_list_ref_sub(bo, put_count, true);

	return 0;
}