#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct radeon_vm {int /*<<< orphan*/  fence; int /*<<< orphan*/ * page_directory; int /*<<< orphan*/ * page_tables; int /*<<< orphan*/  pd_gpu_addr; } ;
struct radeon_sa_bo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa_manager; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int RADEON_GPU_PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_GPU_PAGE_SIZE ; 
 int /*<<< orphan*/ * kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * radeon_sa_bo_cpu_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_sa_bo_free (struct radeon_device*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_sa_bo_gpu_addr (int /*<<< orphan*/ *) ; 
 int radeon_sa_bo_new (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_vm_directory_size (struct radeon_device*) ; 
 int radeon_vm_evict (struct radeon_device*,struct radeon_vm*) ; 
 int radeon_vm_num_pdes (struct radeon_device*) ; 

int radeon_vm_alloc_pt(struct radeon_device *rdev, struct radeon_vm *vm)
{
	unsigned pd_size, pts_size;
	u64 *pd_addr;
	int r;

	if (vm == NULL) {
		return -EINVAL;
	}

	if (vm->page_directory != NULL) {
		return 0;
	}

retry:
	pd_size = RADEON_GPU_PAGE_ALIGN(radeon_vm_directory_size(rdev));
	r = radeon_sa_bo_new(rdev, &rdev->vm_manager.sa_manager,
			     &vm->page_directory, pd_size,
			     RADEON_GPU_PAGE_SIZE, false);
	if (r == -ENOMEM) {
		r = radeon_vm_evict(rdev, vm);
		if (r)
			return r;
		goto retry;

	} else if (r) {
		return r;
	}

	vm->pd_gpu_addr = radeon_sa_bo_gpu_addr(vm->page_directory);

	/* Initially clear the page directory */
	pd_addr = radeon_sa_bo_cpu_addr(vm->page_directory);
	memset(pd_addr, 0, pd_size);

	pts_size = radeon_vm_num_pdes(rdev) * sizeof(struct radeon_sa_bo *);
	vm->page_tables = kzalloc(pts_size, GFP_KERNEL);

	if (vm->page_tables == NULL) {
		DRM_ERROR("Cannot allocate memory for page table array\n");
		radeon_sa_bo_free(rdev, &vm->page_directory, vm->fence);
		return -ENOMEM;
	}

	return 0;
}