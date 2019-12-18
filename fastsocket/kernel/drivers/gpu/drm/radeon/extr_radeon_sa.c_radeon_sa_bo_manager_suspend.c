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
struct radeon_sa_manager {int /*<<< orphan*/ * bo; } ;
struct radeon_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  radeon_bo_kunmap (int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 

int radeon_sa_bo_manager_suspend(struct radeon_device *rdev,
				 struct radeon_sa_manager *sa_manager)
{
	int r;

	if (sa_manager->bo == NULL) {
		dev_err(rdev->dev, "no bo for sa manager\n");
		return -EINVAL;
	}

	r = radeon_bo_reserve(sa_manager->bo, false);
	if (!r) {
		radeon_bo_kunmap(sa_manager->bo);
		radeon_bo_unpin(sa_manager->bo);
		radeon_bo_unreserve(sa_manager->bo);
	}
	return r;
}