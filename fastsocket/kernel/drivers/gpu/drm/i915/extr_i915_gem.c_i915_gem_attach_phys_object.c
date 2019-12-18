#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  filp; } ;
struct drm_i915_gem_object {TYPE_4__* phys_obj; TYPE_2__ base; } ;
struct drm_device {TYPE_5__* dev_private; } ;
struct address_space {int dummy; } ;
struct TYPE_7__ {TYPE_4__** phys_objs; } ;
struct TYPE_11__ {TYPE_1__ mm; } ;
typedef  TYPE_5__ drm_i915_private_t ;
struct TYPE_12__ {struct address_space* i_mapping; } ;
struct TYPE_10__ {int id; TYPE_3__* handle; struct drm_i915_gem_object* cur_obj; } ;
struct TYPE_9__ {char* vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
 int I915_MAX_PHYS_OBJECT ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 TYPE_6__* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_detach_phys_object (struct drm_device*,struct drm_i915_gem_object*) ; 
 int i915_gem_init_phys_object (struct drm_device*,int,int,int) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct page* shmem_read_mapping_page (struct address_space*,int) ; 

int
i915_gem_attach_phys_object(struct drm_device *dev,
			    struct drm_i915_gem_object *obj,
			    int id,
			    int align)
{
	struct address_space *mapping = file_inode(obj->base.filp)->i_mapping;
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret = 0;
	int page_count;
	int i;

	if (id > I915_MAX_PHYS_OBJECT)
		return -EINVAL;

	if (obj->phys_obj) {
		if (obj->phys_obj->id == id)
			return 0;
		i915_gem_detach_phys_object(dev, obj);
	}

	/* create a new object */
	if (!dev_priv->mm.phys_objs[id - 1]) {
		ret = i915_gem_init_phys_object(dev, id,
						obj->base.size, align);
		if (ret) {
			DRM_ERROR("failed to init phys object %d size: %zu\n",
				  id, obj->base.size);
			return ret;
		}
	}

	/* bind to the object */
	obj->phys_obj = dev_priv->mm.phys_objs[id - 1];
	obj->phys_obj->cur_obj = obj;

	page_count = obj->base.size / PAGE_SIZE;

	for (i = 0; i < page_count; i++) {
		struct page *page;
		char *dst, *src;

		page = shmem_read_mapping_page(mapping, i);
		if (IS_ERR(page))
			return PTR_ERR(page);

		src = kmap_atomic(page, KM_USER0);
		dst = obj->phys_obj->handle->vaddr + (i * PAGE_SIZE);
		memcpy(dst, src, PAGE_SIZE);
		kunmap_atomic(src, KM_USER0);

		mark_page_accessed(page);
		page_cache_release(page);
	}

	return 0;
}