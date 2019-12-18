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
struct radeon_device {TYPE_2__* ddev; } ;
struct TYPE_4__ {TYPE_1__* agp; } ;
struct TYPE_3__ {scalar_t__ acquired; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_agp_release (TYPE_2__*) ; 

void radeon_agp_fini(struct radeon_device *rdev)
{
#if __OS_HAS_AGP
	if (rdev->ddev->agp && rdev->ddev->agp->acquired) {
		drm_agp_release(rdev->ddev);
	}
#endif
}