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
struct TYPE_2__ {int enabled; scalar_t__ wb_obj; } ;
struct radeon_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_bo_kunmap (scalar_t__) ; 
 int radeon_bo_reserve (scalar_t__,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (scalar_t__) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

void radeon_wb_disable(struct radeon_device *rdev)
{
	int r;

	if (rdev->wb.wb_obj) {
		r = radeon_bo_reserve(rdev->wb.wb_obj, false);
		if (unlikely(r != 0))
			return;
		radeon_bo_kunmap(rdev->wb.wb_obj);
		radeon_bo_unpin(rdev->wb.wb_obj);
		radeon_bo_unreserve(rdev->wb.wb_obj);
	}
	rdev->wb.enabled = false;
}