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
struct radeon_fence {scalar_t__ seq; int /*<<< orphan*/  ring; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 scalar_t__ RADEON_FENCE_SIGNALED_SEQ ; 
 scalar_t__ radeon_fence_seq_signaled (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

bool radeon_fence_signaled(struct radeon_fence *fence)
{
	if (!fence) {
		return true;
	}
	if (fence->seq == RADEON_FENCE_SIGNALED_SEQ) {
		return true;
	}
	if (radeon_fence_seq_signaled(fence->rdev, fence->seq, fence->ring)) {
		fence->seq = RADEON_FENCE_SIGNALED_SEQ;
		return true;
	}
	return false;
}