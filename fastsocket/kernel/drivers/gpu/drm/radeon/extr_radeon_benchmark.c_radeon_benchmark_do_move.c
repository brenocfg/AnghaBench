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
struct radeon_fence {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
#define  RADEON_BENCHMARK_COPY_BLIT 129 
#define  RADEON_BENCHMARK_COPY_DMA 128 
 unsigned int RADEON_GPU_PAGE_SIZE ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 int radeon_copy_blit (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct radeon_fence**) ; 
 int radeon_copy_dma (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct radeon_fence**) ; 
 int /*<<< orphan*/  radeon_fence_unref (struct radeon_fence**) ; 
 int radeon_fence_wait (struct radeon_fence*,int) ; 

__attribute__((used)) static int radeon_benchmark_do_move(struct radeon_device *rdev, unsigned size,
				    uint64_t saddr, uint64_t daddr,
				    int flag, int n)
{
	unsigned long start_jiffies;
	unsigned long end_jiffies;
	struct radeon_fence *fence = NULL;
	int i, r;

	start_jiffies = jiffies;
	for (i = 0; i < n; i++) {
		switch (flag) {
		case RADEON_BENCHMARK_COPY_DMA:
			r = radeon_copy_dma(rdev, saddr, daddr,
					    size / RADEON_GPU_PAGE_SIZE,
					    &fence);
			break;
		case RADEON_BENCHMARK_COPY_BLIT:
			r = radeon_copy_blit(rdev, saddr, daddr,
					     size / RADEON_GPU_PAGE_SIZE,
					     &fence);
			break;
		default:
			DRM_ERROR("Unknown copy method\n");
			r = -EINVAL;
		}
		if (r)
			goto exit_do_move;
		r = radeon_fence_wait(fence, false);
		if (r)
			goto exit_do_move;
		radeon_fence_unref(&fence);
	}
	end_jiffies = jiffies;
	r = jiffies_to_msecs(end_jiffies - start_jiffies);

exit_do_move:
	if (fence)
		radeon_fence_unref(&fence);
	return r;
}