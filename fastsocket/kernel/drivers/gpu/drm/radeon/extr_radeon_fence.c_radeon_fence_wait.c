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
struct radeon_fence {int /*<<< orphan*/  seq; int /*<<< orphan*/  ring; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RADEON_FENCE_SIGNALED_SEQ ; 
 int /*<<< orphan*/  WARN (int,char*,struct radeon_fence*) ; 
 int radeon_fence_wait_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int radeon_fence_wait(struct radeon_fence *fence, bool intr)
{
	int r;

	if (fence == NULL) {
		WARN(1, "Querying an invalid fence : %p !\n", fence);
		return -EINVAL;
	}

	r = radeon_fence_wait_seq(fence->rdev, fence->seq,
				  fence->ring, intr, true);
	if (r) {
		return r;
	}
	fence->seq = RADEON_FENCE_SIGNALED_SEQ;
	return 0;
}