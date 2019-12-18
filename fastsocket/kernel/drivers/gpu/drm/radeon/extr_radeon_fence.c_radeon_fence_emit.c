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
struct radeon_fence {int ring; scalar_t__ seq; struct radeon_device* rdev; int /*<<< orphan*/  kref; } ;
struct radeon_device {int /*<<< orphan*/  ddev; TYPE_1__* fence_drv; } ;
struct TYPE_2__ {scalar_t__* sync_seq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct radeon_fence* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_fence_ring_emit (struct radeon_device*,int,struct radeon_fence*) ; 
 int /*<<< orphan*/  trace_radeon_fence_emit (int /*<<< orphan*/ ,scalar_t__) ; 

int radeon_fence_emit(struct radeon_device *rdev,
		      struct radeon_fence **fence,
		      int ring)
{
	/* we are protected by the ring emission mutex */
	*fence = kmalloc(sizeof(struct radeon_fence), GFP_KERNEL);
	if ((*fence) == NULL) {
		return -ENOMEM;
	}
	kref_init(&((*fence)->kref));
	(*fence)->rdev = rdev;
	(*fence)->seq = ++rdev->fence_drv[ring].sync_seq[ring];
	(*fence)->ring = ring;
	radeon_fence_ring_emit(rdev, ring, *fence);
	trace_radeon_fence_emit(rdev->ddev, (*fence)->seq);
	return 0;
}