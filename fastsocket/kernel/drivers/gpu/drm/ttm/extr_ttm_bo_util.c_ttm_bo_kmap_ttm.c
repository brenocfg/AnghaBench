#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_tt {scalar_t__ state; int /*<<< orphan*/ * pages; TYPE_2__* bdev; } ;
struct ttm_mem_reg {int placement; } ;
struct ttm_buffer_object {struct ttm_tt* ttm; struct ttm_mem_reg mem; } ;
struct ttm_bo_kmap_obj {int /*<<< orphan*/  virtual; int /*<<< orphan*/  bo_kmap_type; int /*<<< orphan*/  page; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* ttm_tt_populate ) (struct ttm_tt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int TTM_PL_FLAG_CACHED ; 
 int /*<<< orphan*/  kmap (int /*<<< orphan*/ ) ; 
 int stub1 (struct ttm_tt*) ; 
 scalar_t__ tt_unpopulated ; 
 int /*<<< orphan*/  ttm_bo_map_kmap ; 
 int /*<<< orphan*/  ttm_bo_map_vmap ; 
 int /*<<< orphan*/  ttm_io_prot (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmap (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttm_bo_kmap_ttm(struct ttm_buffer_object *bo,
			   unsigned long start_page,
			   unsigned long num_pages,
			   struct ttm_bo_kmap_obj *map)
{
	struct ttm_mem_reg *mem = &bo->mem; pgprot_t prot;
	struct ttm_tt *ttm = bo->ttm;
	int ret;

	BUG_ON(!ttm);

	if (ttm->state == tt_unpopulated) {
		ret = ttm->bdev->driver->ttm_tt_populate(ttm);
		if (ret)
			return ret;
	}

	if (num_pages == 1 && (mem->placement & TTM_PL_FLAG_CACHED)) {
		/*
		 * We're mapping a single page, and the desired
		 * page protection is consistent with the bo.
		 */

		map->bo_kmap_type = ttm_bo_map_kmap;
		map->page = ttm->pages[start_page];
		map->virtual = kmap(map->page);
	} else {
		/*
		 * We need to use vmap to get the desired page protection
		 * or to make the buffer object look contiguous.
		 */
		prot = (mem->placement & TTM_PL_FLAG_CACHED) ?
			PAGE_KERNEL :
			ttm_io_prot(mem->placement, PAGE_KERNEL);
		map->bo_kmap_type = ttm_bo_map_vmap;
		map->virtual = vmap(ttm->pages + start_page, num_pages,
				    0, prot);
	}
	return (!map->virtual) ? -ENOMEM : 0;
}