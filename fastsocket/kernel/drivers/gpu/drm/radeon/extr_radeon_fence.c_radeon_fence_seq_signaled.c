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
typedef  scalar_t__ u64 ;
struct radeon_device {TYPE_1__* fence_drv; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_seq; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_fence_process (struct radeon_device*,unsigned int) ; 

__attribute__((used)) static bool radeon_fence_seq_signaled(struct radeon_device *rdev,
				      u64 seq, unsigned ring)
{
	if (atomic64_read(&rdev->fence_drv[ring].last_seq) >= seq) {
		return true;
	}
	/* poll new last sequence at least once */
	radeon_fence_process(rdev, ring);
	if (atomic64_read(&rdev->fence_drv[ring].last_seq) >= seq) {
		return true;
	}
	return false;
}