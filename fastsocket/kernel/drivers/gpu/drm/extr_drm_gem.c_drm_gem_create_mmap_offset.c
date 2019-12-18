#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct drm_map_list {struct drm_local_map* map; TYPE_1__* file_offset_node; TYPE_5__ hash; } ;
struct drm_local_map {int size; struct drm_gem_object* handle; int /*<<< orphan*/  type; } ;
struct drm_gem_object {int size; int /*<<< orphan*/  name; struct drm_map_list map_list; struct drm_device* dev; } ;
struct drm_gem_mm {int /*<<< orphan*/  offset_hash; int /*<<< orphan*/  offset_manager; } ;
struct drm_device {struct drm_gem_mm* mm_private; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  _DRM_GEM ; 
 int drm_ht_insert_item (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_1__* drm_mm_get_block (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_put_block (TYPE_1__*) ; 
 TYPE_1__* drm_mm_search_free (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct drm_local_map*) ; 
 struct drm_local_map* kzalloc (int,int /*<<< orphan*/ ) ; 

int
drm_gem_create_mmap_offset(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct drm_gem_mm *mm = dev->mm_private;
	struct drm_map_list *list;
	struct drm_local_map *map;
	int ret;

	/* Set the object up for mmap'ing */
	list = &obj->map_list;
	list->map = kzalloc(sizeof(struct drm_map_list), GFP_KERNEL);
	if (!list->map)
		return -ENOMEM;

	map = list->map;
	map->type = _DRM_GEM;
	map->size = obj->size;
	map->handle = obj;

	/* Get a DRM GEM mmap offset allocated... */
	list->file_offset_node = drm_mm_search_free(&mm->offset_manager,
			obj->size / PAGE_SIZE, 0, false);

	if (!list->file_offset_node) {
		DRM_ERROR("failed to allocate offset for bo %d\n", obj->name);
		ret = -ENOSPC;
		goto out_free_list;
	}

	list->file_offset_node = drm_mm_get_block(list->file_offset_node,
			obj->size / PAGE_SIZE, 0);
	if (!list->file_offset_node) {
		ret = -ENOMEM;
		goto out_free_list;
	}

	list->hash.key = list->file_offset_node->start;
	ret = drm_ht_insert_item(&mm->offset_hash, &list->hash);
	if (ret) {
		DRM_ERROR("failed to add to map hash\n");
		goto out_free_mm;
	}

	return 0;

out_free_mm:
	drm_mm_put_block(list->file_offset_node);
out_free_list:
	kfree(list->map);
	list->map = NULL;

	return ret;
}