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
struct radeon_device {TYPE_1__* fence_drv; } ;
struct TYPE_2__ {int scratch_reg; int initialized; int /*<<< orphan*/  last_activity; int /*<<< orphan*/  last_seq; scalar_t__* sync_seq; scalar_t__ gpu_addr; int /*<<< orphan*/ * cpu_addr; } ;

/* Variables and functions */
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void radeon_fence_driver_init_ring(struct radeon_device *rdev, int ring)
{
	int i;

	rdev->fence_drv[ring].scratch_reg = -1;
	rdev->fence_drv[ring].cpu_addr = NULL;
	rdev->fence_drv[ring].gpu_addr = 0;
	for (i = 0; i < RADEON_NUM_RINGS; ++i)
		rdev->fence_drv[ring].sync_seq[i] = 0;
	atomic64_set(&rdev->fence_drv[ring].last_seq, 0);
	rdev->fence_drv[ring].last_activity = jiffies;
	rdev->fence_drv[ring].initialized = false;
}