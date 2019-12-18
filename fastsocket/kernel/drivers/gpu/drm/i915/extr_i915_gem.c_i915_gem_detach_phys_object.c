#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  filp; } ;
struct drm_i915_gem_object {TYPE_3__* phys_obj; TYPE_2__ base; } ;
struct drm_device {int dummy; } ;
struct address_space {int dummy; } ;
struct TYPE_8__ {struct address_space* i_mapping; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cur_obj; TYPE_1__* handle; } ;
struct TYPE_5__ {char* vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  drm_clflush_pages (struct page**,int) ; 
 TYPE_4__* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_chipset_flush (struct drm_device*) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 struct page* shmem_read_mapping_page (struct address_space*,int) ; 

void i915_gem_detach_phys_object(struct drm_device *dev,
				 struct drm_i915_gem_object *obj)
{
	struct address_space *mapping = file_inode(obj->base.filp)->i_mapping;
	char *vaddr;
	int i;
	int page_count;

	if (!obj->phys_obj)
		return;
	vaddr = obj->phys_obj->handle->vaddr;

	page_count = obj->base.size / PAGE_SIZE;
	for (i = 0; i < page_count; i++) {
		struct page *page = shmem_read_mapping_page(mapping, i);
		if (!IS_ERR(page)) {
			char *dst = kmap_atomic(page, KM_USER0);
			memcpy(dst, vaddr + i*PAGE_SIZE, PAGE_SIZE);
			kunmap_atomic(dst, KM_USER0);

			drm_clflush_pages(&page, 1);

			set_page_dirty(page);
			mark_page_accessed(page);
			page_cache_release(page);
		}
	}
	i915_gem_chipset_flush(dev);

	obj->phys_obj->cur_obj = NULL;
	obj->phys_obj = NULL;
}