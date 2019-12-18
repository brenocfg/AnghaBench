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
typedef  scalar_t__ uint64_t ;
struct radeon_semaphore {int /*<<< orphan*/  sa_bo; int /*<<< orphan*/  gpu_addr; scalar_t__ waiters; } ;
struct radeon_device {int /*<<< orphan*/  ring_tmp_bo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct radeon_semaphore*) ; 
 struct radeon_semaphore* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ radeon_sa_bo_cpu_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_sa_bo_gpu_addr (int /*<<< orphan*/ ) ; 
 int radeon_sa_bo_new (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

int radeon_semaphore_create(struct radeon_device *rdev,
			    struct radeon_semaphore **semaphore)
{
	int r;

	*semaphore = kmalloc(sizeof(struct radeon_semaphore), GFP_KERNEL);
	if (*semaphore == NULL) {
		return -ENOMEM;
	}
	r = radeon_sa_bo_new(rdev, &rdev->ring_tmp_bo,
			     &(*semaphore)->sa_bo, 8, 8, true);
	if (r) {
		kfree(*semaphore);
		*semaphore = NULL;
		return r;
	}
	(*semaphore)->waiters = 0;
	(*semaphore)->gpu_addr = radeon_sa_bo_gpu_addr((*semaphore)->sa_bo);
	*((uint64_t*)radeon_sa_bo_cpu_addr((*semaphore)->sa_bo)) = 0;
	return 0;
}