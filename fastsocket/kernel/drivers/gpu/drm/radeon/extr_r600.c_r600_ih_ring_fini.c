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
struct TYPE_2__ {int /*<<< orphan*/ * ring_obj; int /*<<< orphan*/ * ring; } ;
struct radeon_device {TYPE_1__ ih; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  radeon_bo_kunmap (int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 

void r600_ih_ring_fini(struct radeon_device *rdev)
{
	int r;
	if (rdev->ih.ring_obj) {
		r = radeon_bo_reserve(rdev->ih.ring_obj, false);
		if (likely(r == 0)) {
			radeon_bo_kunmap(rdev->ih.ring_obj);
			radeon_bo_unpin(rdev->ih.ring_obj);
			radeon_bo_unreserve(rdev->ih.ring_obj);
		}
		radeon_bo_unref(&rdev->ih.ring_obj);
		rdev->ih.ring = NULL;
		rdev->ih.ring_obj = NULL;
	}
}