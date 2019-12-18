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
struct drm_mm {int dummy; } ;
struct ttm_range_manager {int /*<<< orphan*/  lock; struct drm_mm mm; } ;
struct ttm_mem_type_manager {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ drm_mm_clean (struct drm_mm*) ; 
 int /*<<< orphan*/  drm_mm_takedown (struct drm_mm*) ; 
 int /*<<< orphan*/  kfree (struct ttm_range_manager*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ttm_bo_man_takedown(struct ttm_mem_type_manager *man)
{
	struct ttm_range_manager *rman = (struct ttm_range_manager *) man->priv;
	struct drm_mm *mm = &rman->mm;

	spin_lock(&rman->lock);
	if (drm_mm_clean(mm)) {
		drm_mm_takedown(mm);
		spin_unlock(&rman->lock);
		kfree(rman);
		man->priv = NULL;
		return 0;
	}
	spin_unlock(&rman->lock);
	return -EBUSY;
}