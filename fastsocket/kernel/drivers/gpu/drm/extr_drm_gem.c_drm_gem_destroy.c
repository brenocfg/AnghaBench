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
struct drm_device {struct drm_gem_mm* mm_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_ht_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_gem_mm*) ; 

void
drm_gem_destroy(struct drm_device *dev)
{
	struct drm_gem_mm *mm = dev->mm_private;

	drm_mm_takedown(&mm->offset_manager);
	drm_ht_remove(&mm->offset_hash);
	kfree(mm);
	dev->mm_private = NULL;
}