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
struct radeon_bo {TYPE_1__* rdev; int /*<<< orphan*/  tbo; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct radeon_bo*) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int radeon_bo_reserve(struct radeon_bo *bo, bool no_intr)
{
	int r;

	r = ttm_bo_reserve(&bo->tbo, !no_intr, false, false, 0);
	if (unlikely(r != 0)) {
		if (r != -ERESTARTSYS)
			dev_err(bo->rdev->dev, "%p reserve failed\n", bo);
		return r;
	}
	return 0;
}