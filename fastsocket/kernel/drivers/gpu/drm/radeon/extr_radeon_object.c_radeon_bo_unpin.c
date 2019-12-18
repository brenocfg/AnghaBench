#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_placement; } ;
struct radeon_bo {TYPE_1__* rdev; TYPE_2__ placement; int /*<<< orphan*/  tbo; int /*<<< orphan*/ * placements; scalar_t__ pin_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct radeon_bo*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,struct radeon_bo*) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 scalar_t__ unlikely (int) ; 

int radeon_bo_unpin(struct radeon_bo *bo)
{
	int r, i;

	if (!bo->pin_count) {
		dev_warn(bo->rdev->dev, "%p unpin not necessary\n", bo);
		return 0;
	}
	bo->pin_count--;
	if (bo->pin_count)
		return 0;
	for (i = 0; i < bo->placement.num_placement; i++)
		bo->placements[i] &= ~TTM_PL_FLAG_NO_EVICT;
	r = ttm_bo_validate(&bo->tbo, &bo->placement, false, false);
	if (unlikely(r != 0))
		dev_err(bo->rdev->dev, "%p validate failed for unpin\n", bo);
	return r;
}