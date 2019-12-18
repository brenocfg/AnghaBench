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
struct radeon_fence_driver {scalar_t__* sync_seq; } ;
struct radeon_fence {int ring; scalar_t__ seq; TYPE_1__* rdev; } ;
struct TYPE_2__ {struct radeon_fence_driver* fence_drv; } ;

/* Variables and functions */

bool radeon_fence_need_sync(struct radeon_fence *fence, int dst_ring)
{
	struct radeon_fence_driver *fdrv;

	if (!fence) {
		return false;
	}

	if (fence->ring == dst_ring) {
		return false;
	}

	/* we are protected by the ring mutex */
	fdrv = &fence->rdev->fence_drv[dst_ring];
	if (fence->seq <= fdrv->sync_seq[fence->ring]) {
		return false;
	}

	return true;
}