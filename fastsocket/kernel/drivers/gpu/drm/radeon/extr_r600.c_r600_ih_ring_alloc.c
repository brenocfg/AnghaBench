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
struct TYPE_2__ {int /*<<< orphan*/ * ring_obj; int /*<<< orphan*/  ring; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  ring_size; } ;
struct radeon_device {TYPE_1__ ih; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_GTT ; 
 int radeon_bo_create (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int radeon_bo_kmap (int /*<<< orphan*/ *,void**) ; 
 int radeon_bo_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int r600_ih_ring_alloc(struct radeon_device *rdev)
{
	int r;

	/* Allocate ring buffer */
	if (rdev->ih.ring_obj == NULL) {
		r = radeon_bo_create(rdev, rdev->ih.ring_size,
				     PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT,
				     NULL, &rdev->ih.ring_obj);
		if (r) {
			DRM_ERROR("radeon: failed to create ih ring buffer (%d).\n", r);
			return r;
		}
		r = radeon_bo_reserve(rdev->ih.ring_obj, false);
		if (unlikely(r != 0))
			return r;
		r = radeon_bo_pin(rdev->ih.ring_obj,
				  RADEON_GEM_DOMAIN_GTT,
				  &rdev->ih.gpu_addr);
		if (r) {
			radeon_bo_unreserve(rdev->ih.ring_obj);
			DRM_ERROR("radeon: failed to pin ih ring buffer (%d).\n", r);
			return r;
		}
		r = radeon_bo_kmap(rdev->ih.ring_obj,
				   (void **)&rdev->ih.ring);
		radeon_bo_unreserve(rdev->ih.ring_obj);
		if (r) {
			DRM_ERROR("radeon: failed to map ih ring buffer (%d).\n", r);
			return r;
		}
	}
	return 0;
}