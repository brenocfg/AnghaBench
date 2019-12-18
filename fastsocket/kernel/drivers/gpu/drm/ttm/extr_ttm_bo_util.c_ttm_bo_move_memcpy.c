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
struct ttm_tt {scalar_t__ state; TYPE_2__* bdev; } ;
struct ttm_mem_type_manager {int flags; } ;
struct ttm_mem_reg {size_t mem_type; scalar_t__ start; scalar_t__ size; int num_pages; int /*<<< orphan*/ * mm_node; int /*<<< orphan*/  placement; } ;
struct ttm_buffer_object {struct ttm_tt* ttm; struct ttm_mem_reg mem; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {struct ttm_mem_type_manager* man; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* ttm_tt_populate ) (struct ttm_tt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int TTM_MEMTYPE_FLAG_FIXED ; 
 int /*<<< orphan*/  mb () ; 
 int stub1 (struct ttm_tt*) ; 
 scalar_t__ tt_unpopulated ; 
 int /*<<< orphan*/  ttm_bo_mem_put (struct ttm_buffer_object*,struct ttm_mem_reg*) ; 
 int ttm_copy_io_page (void*,void*,unsigned long) ; 
 int ttm_copy_io_ttm_page (struct ttm_tt*,void*,unsigned long,int /*<<< orphan*/ ) ; 
 int ttm_copy_ttm_io_page (struct ttm_tt*,void*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_io_prot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_mem_reg_ioremap (struct ttm_bo_device*,struct ttm_mem_reg*,void**) ; 
 int /*<<< orphan*/  ttm_mem_reg_iounmap (struct ttm_bo_device*,struct ttm_mem_reg*,void*) ; 
 int /*<<< orphan*/  ttm_tt_destroy (struct ttm_tt*) ; 
 int /*<<< orphan*/  ttm_tt_unbind (struct ttm_tt*) ; 

int ttm_bo_move_memcpy(struct ttm_buffer_object *bo,
		       bool evict, bool no_wait_gpu,
		       struct ttm_mem_reg *new_mem)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_mem_type_manager *man = &bdev->man[new_mem->mem_type];
	struct ttm_tt *ttm = bo->ttm;
	struct ttm_mem_reg *old_mem = &bo->mem;
	struct ttm_mem_reg old_copy = *old_mem;
	void *old_iomap;
	void *new_iomap;
	int ret;
	unsigned long i;
	unsigned long page;
	unsigned long add = 0;
	int dir;

	ret = ttm_mem_reg_ioremap(bdev, old_mem, &old_iomap);
	if (ret)
		return ret;
	ret = ttm_mem_reg_ioremap(bdev, new_mem, &new_iomap);
	if (ret)
		goto out;

	if (old_iomap == NULL && new_iomap == NULL)
		goto out2;
	if (old_iomap == NULL && ttm == NULL)
		goto out2;

	if (ttm->state == tt_unpopulated) {
		ret = ttm->bdev->driver->ttm_tt_populate(ttm);
		if (ret) {
			/* if we fail here don't nuke the mm node
			 * as the bo still owns it */
			old_copy.mm_node = NULL;
			goto out1;
		}
	}

	add = 0;
	dir = 1;

	if ((old_mem->mem_type == new_mem->mem_type) &&
	    (new_mem->start < old_mem->start + old_mem->size)) {
		dir = -1;
		add = new_mem->num_pages - 1;
	}

	for (i = 0; i < new_mem->num_pages; ++i) {
		page = i * dir + add;
		if (old_iomap == NULL) {
			pgprot_t prot = ttm_io_prot(old_mem->placement,
						    PAGE_KERNEL);
			ret = ttm_copy_ttm_io_page(ttm, new_iomap, page,
						   prot);
		} else if (new_iomap == NULL) {
			pgprot_t prot = ttm_io_prot(new_mem->placement,
						    PAGE_KERNEL);
			ret = ttm_copy_io_ttm_page(ttm, old_iomap, page,
						   prot);
		} else
			ret = ttm_copy_io_page(new_iomap, old_iomap, page);
		if (ret) {
			/* failing here, means keep old copy as-is */
			old_copy.mm_node = NULL;
			goto out1;
		}
	}
	mb();
out2:
	old_copy = *old_mem;
	*old_mem = *new_mem;
	new_mem->mm_node = NULL;

	if ((man->flags & TTM_MEMTYPE_FLAG_FIXED) && (ttm != NULL)) {
		ttm_tt_unbind(ttm);
		ttm_tt_destroy(ttm);
		bo->ttm = NULL;
	}

out1:
	ttm_mem_reg_iounmap(bdev, old_mem, new_iomap);
out:
	ttm_mem_reg_iounmap(bdev, &old_copy, old_iomap);
	ttm_bo_mem_put(bo, &old_copy);
	return ret;
}