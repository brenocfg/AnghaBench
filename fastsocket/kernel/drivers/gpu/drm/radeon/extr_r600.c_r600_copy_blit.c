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
typedef  int /*<<< orphan*/  uint64_t ;
struct radeon_semaphore {int dummy; } ;
struct radeon_sa_bo {int dummy; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r600_blit_done_copy (struct radeon_device*,struct radeon_fence**,struct radeon_sa_bo*,struct radeon_semaphore*) ; 
 int r600_blit_prepare_copy (struct radeon_device*,unsigned int,struct radeon_fence**,struct radeon_sa_bo**,struct radeon_semaphore**) ; 
 int /*<<< orphan*/  r600_kms_blit_copy (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct radeon_sa_bo*) ; 

int r600_copy_blit(struct radeon_device *rdev,
		   uint64_t src_offset,
		   uint64_t dst_offset,
		   unsigned num_gpu_pages,
		   struct radeon_fence **fence)
{
	struct radeon_semaphore *sem = NULL;
	struct radeon_sa_bo *vb = NULL;
	int r;

	r = r600_blit_prepare_copy(rdev, num_gpu_pages, fence, &vb, &sem);
	if (r) {
		return r;
	}
	r600_kms_blit_copy(rdev, src_offset, dst_offset, num_gpu_pages, vb);
	r600_blit_done_copy(rdev, fence, vb, sem);
	return 0;
}