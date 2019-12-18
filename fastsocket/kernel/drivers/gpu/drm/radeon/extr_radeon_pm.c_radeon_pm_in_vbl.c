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
struct TYPE_2__ {int active_crtcs; } ;
struct radeon_device {int num_crtc; int /*<<< orphan*/  ddev; TYPE_1__ pm; } ;

/* Variables and functions */
 int DRM_SCANOUTPOS_INVBL ; 
 int DRM_SCANOUTPOS_VALID ; 
 int radeon_get_crtc_scanoutpos (int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static bool radeon_pm_in_vbl(struct radeon_device *rdev)
{
	int  crtc, vpos, hpos, vbl_status;
	bool in_vbl = true;

	/* Iterate over all active crtc's. All crtc's must be in vblank,
	 * otherwise return in_vbl == false.
	 */
	for (crtc = 0; (crtc < rdev->num_crtc) && in_vbl; crtc++) {
		if (rdev->pm.active_crtcs & (1 << crtc)) {
			vbl_status = radeon_get_crtc_scanoutpos(rdev->ddev, crtc, &vpos, &hpos);
			if ((vbl_status & DRM_SCANOUTPOS_VALID) &&
			    !(vbl_status & DRM_SCANOUTPOS_INVBL))
				in_vbl = false;
		}
	}

	return in_vbl;
}