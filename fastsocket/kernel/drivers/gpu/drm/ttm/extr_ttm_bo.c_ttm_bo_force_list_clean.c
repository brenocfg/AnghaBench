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
struct ttm_mem_type_manager {int /*<<< orphan*/  lru; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;
struct ttm_bo_device {struct ttm_bo_global* glob; struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ttm_mem_evict_first (struct ttm_bo_device*,unsigned int,int,int) ; 

__attribute__((used)) static int ttm_bo_force_list_clean(struct ttm_bo_device *bdev,
					unsigned mem_type, bool allow_errors)
{
	struct ttm_mem_type_manager *man = &bdev->man[mem_type];
	struct ttm_bo_global *glob = bdev->glob;
	int ret;

	/*
	 * Can't use standard list traversal since we're unlocking.
	 */

	spin_lock(&glob->lru_lock);
	while (!list_empty(&man->lru)) {
		spin_unlock(&glob->lru_lock);
		ret = ttm_mem_evict_first(bdev, mem_type, false, false);
		if (ret) {
			if (allow_errors) {
				return ret;
			} else {
				pr_err("Cleanup eviction failed\n");
			}
		}
		spin_lock(&glob->lru_lock);
	}
	spin_unlock(&glob->lru_lock);
	return 0;
}