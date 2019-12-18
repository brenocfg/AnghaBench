#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct ttm_mem_reg {int start; scalar_t__ mem_type; } ;
struct radeon_vm {int /*<<< orphan*/  last_flush; int /*<<< orphan*/  fence; int /*<<< orphan*/ * page_directory; } ;
struct radeon_ib {int /*<<< orphan*/  fence; scalar_t__ length_dw; } ;
struct TYPE_6__ {scalar_t__ vram_base_offset; } ;
struct radeon_device {TYPE_3__ vm_manager; int /*<<< orphan*/  dev; TYPE_2__* asic; } ;
struct radeon_bo_va {int valid; int /*<<< orphan*/  flags; int /*<<< orphan*/  eoffset; int /*<<< orphan*/  soffset; } ;
struct radeon_bo {int dummy; } ;
struct TYPE_4__ {unsigned int pt_ring_index; } ;
struct TYPE_5__ {TYPE_1__ vm; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 unsigned int RADEON_VM_BLOCK_SIZE ; 
 int /*<<< orphan*/  RADEON_VM_PAGE_SYSTEM ; 
 int /*<<< orphan*/  RADEON_VM_PAGE_VALID ; 
 scalar_t__ TTM_PL_SYSTEM ; 
 scalar_t__ TTM_PL_TT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct radeon_bo*,struct radeon_vm*) ; 
 unsigned int radeon_bo_ngpu_pages (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_fence_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_fence_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_ib_free (struct radeon_device*,struct radeon_ib*) ; 
 int radeon_ib_get (struct radeon_device*,unsigned int,struct radeon_ib*,int /*<<< orphan*/ *,unsigned int) ; 
 int radeon_ib_schedule (struct radeon_device*,struct radeon_ib*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_ib_sync_to (struct radeon_ib*,int /*<<< orphan*/ ) ; 
 struct radeon_bo_va* radeon_vm_bo_find (struct radeon_vm*,struct radeon_bo*) ; 
 int radeon_vm_update_pdes (struct radeon_device*,struct radeon_vm*,struct radeon_ib*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_vm_update_ptes (struct radeon_device*,struct radeon_vm*,struct radeon_ib*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int radeon_vm_bo_update_pte(struct radeon_device *rdev,
			    struct radeon_vm *vm,
			    struct radeon_bo *bo,
			    struct ttm_mem_reg *mem)
{
	unsigned ridx = rdev->asic->vm.pt_ring_index;
	struct radeon_ib ib;
	struct radeon_bo_va *bo_va;
	unsigned nptes, npdes, ndw;
	uint64_t addr;
	int r;

	/* nothing to do if vm isn't bound */
	if (vm->page_directory == NULL)
		return 0;

	bo_va = radeon_vm_bo_find(vm, bo);
	if (bo_va == NULL) {
		dev_err(rdev->dev, "bo %p not in vm %p\n", bo, vm);
		return -EINVAL;
	}

	if (!bo_va->soffset) {
		dev_err(rdev->dev, "bo %p don't has a mapping in vm %p\n",
			bo, vm);
		return -EINVAL;
	}

	if ((bo_va->valid && mem) || (!bo_va->valid && mem == NULL))
		return 0;

	bo_va->flags &= ~RADEON_VM_PAGE_VALID;
	bo_va->flags &= ~RADEON_VM_PAGE_SYSTEM;
	if (mem) {
		addr = mem->start << PAGE_SHIFT;
		if (mem->mem_type != TTM_PL_SYSTEM) {
			bo_va->flags |= RADEON_VM_PAGE_VALID;
			bo_va->valid = true;
		}
		if (mem->mem_type == TTM_PL_TT) {
			bo_va->flags |= RADEON_VM_PAGE_SYSTEM;
		} else {
			addr += rdev->vm_manager.vram_base_offset;
		}
	} else {
		addr = 0;
		bo_va->valid = false;
	}

	nptes = radeon_bo_ngpu_pages(bo);

	/* assume two extra pdes in case the mapping overlaps the borders */
	npdes = (nptes >> RADEON_VM_BLOCK_SIZE) + 2;

	/* padding, etc. */
	ndw = 64;

	if (RADEON_VM_BLOCK_SIZE > 11)
		/* reserve space for one header for every 2k dwords */
		ndw += (nptes >> 11) * 4;
	else
		/* reserve space for one header for
		    every (1 << BLOCK_SIZE) entries */
		ndw += (nptes >> RADEON_VM_BLOCK_SIZE) * 4;

	/* reserve space for pte addresses */
	ndw += nptes * 2;

	/* reserve space for one header for every 2k dwords */
	ndw += (npdes >> 11) * 4;

	/* reserve space for pde addresses */
	ndw += npdes * 2;

	/* update too big for an IB */
	if (ndw > 0xfffff)
		return -ENOMEM;

	r = radeon_ib_get(rdev, ridx, &ib, NULL, ndw * 4);
	ib.length_dw = 0;

	r = radeon_vm_update_pdes(rdev, vm, &ib, bo_va->soffset, bo_va->eoffset);
	if (r) {
		radeon_ib_free(rdev, &ib);
		return r;
	}

	radeon_vm_update_ptes(rdev, vm, &ib, bo_va->soffset, bo_va->eoffset,
			      addr, bo_va->flags);

	radeon_ib_sync_to(&ib, vm->fence);
	r = radeon_ib_schedule(rdev, &ib, NULL);
	if (r) {
		radeon_ib_free(rdev, &ib);
		return r;
	}
	radeon_fence_unref(&vm->fence);
	vm->fence = radeon_fence_ref(ib.fence);
	radeon_ib_free(rdev, &ib);
	radeon_fence_unref(&vm->last_flush);

	return 0;
}