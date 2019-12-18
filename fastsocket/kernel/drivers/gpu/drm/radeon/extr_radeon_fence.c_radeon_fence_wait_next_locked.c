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
typedef  scalar_t__ uint64_t ;
struct radeon_device {TYPE_1__* fence_drv; } ;
struct TYPE_2__ {scalar_t__* sync_seq; int /*<<< orphan*/  last_seq; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int radeon_fence_wait_seq (struct radeon_device*,scalar_t__,int,int,int) ; 

int radeon_fence_wait_next_locked(struct radeon_device *rdev, int ring)
{
	uint64_t seq;

	seq = atomic64_read(&rdev->fence_drv[ring].last_seq) + 1ULL;
	if (seq >= rdev->fence_drv[ring].sync_seq[ring]) {
		/* nothing to wait for, last_seq is
		   already the last emited fence */
		return -ENOENT;
	}
	return radeon_fence_wait_seq(rdev, seq, ring, false, false);
}