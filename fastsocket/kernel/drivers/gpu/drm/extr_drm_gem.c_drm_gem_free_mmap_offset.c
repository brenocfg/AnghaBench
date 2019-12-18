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
struct drm_map_list {int /*<<< orphan*/ * map; int /*<<< orphan*/  file_offset_node; int /*<<< orphan*/  hash; } ;
struct drm_gem_object {struct drm_map_list map_list; struct drm_device* dev; } ;
struct drm_gem_mm {int /*<<< orphan*/  offset_hash; } ;
struct drm_device {struct drm_gem_mm* mm_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_ht_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_put_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void
drm_gem_free_mmap_offset(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct drm_gem_mm *mm = dev->mm_private;
	struct drm_map_list *list = &obj->map_list;

	drm_ht_remove_item(&mm->offset_hash, &list->hash);
	drm_mm_put_block(list->file_offset_node);
	kfree(list->map);
	list->map = NULL;
}