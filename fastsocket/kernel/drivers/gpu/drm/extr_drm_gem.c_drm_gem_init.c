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
struct drm_gem_mm {int /*<<< orphan*/  offset_hash; int /*<<< orphan*/  offset_manager; } ;
struct drm_device {struct drm_gem_mm* mm_private; int /*<<< orphan*/  object_name_idr; int /*<<< orphan*/  object_name_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET_SIZE ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET_START ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ drm_ht_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_ht_remove (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_gem_mm*) ; 
 struct drm_gem_mm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
drm_gem_init(struct drm_device *dev)
{
	struct drm_gem_mm *mm;

	spin_lock_init(&dev->object_name_lock);
	idr_init(&dev->object_name_idr);

	mm = kzalloc(sizeof(struct drm_gem_mm), GFP_KERNEL);
	if (!mm) {
		DRM_ERROR("out of memory\n");
		return -ENOMEM;
	}

	dev->mm_private = mm;

	if (drm_ht_create(&mm->offset_hash, 12)) {
		kfree(mm);
		return -ENOMEM;
	}

	if (drm_mm_init(&mm->offset_manager, DRM_FILE_PAGE_OFFSET_START,
			DRM_FILE_PAGE_OFFSET_SIZE)) {
		drm_ht_remove(&mm->offset_hash);
		kfree(mm);
		return -ENOMEM;
	}

	return 0;
}