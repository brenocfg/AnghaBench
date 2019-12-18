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
struct TYPE_2__ {int ready; int /*<<< orphan*/ * pages_addr; int /*<<< orphan*/ * pages; int /*<<< orphan*/  num_cpu_pages; } ;
struct radeon_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_dummy_page_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gart_unbind (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void radeon_gart_fini(struct radeon_device *rdev)
{
	if (rdev->gart.pages && rdev->gart.pages_addr && rdev->gart.ready) {
		/* unbind pages */
		radeon_gart_unbind(rdev, 0, rdev->gart.num_cpu_pages);
	}
	rdev->gart.ready = false;
	vfree(rdev->gart.pages);
	vfree(rdev->gart.pages_addr);
	rdev->gart.pages = NULL;
	rdev->gart.pages_addr = NULL;

	radeon_dummy_page_fini(rdev);
}