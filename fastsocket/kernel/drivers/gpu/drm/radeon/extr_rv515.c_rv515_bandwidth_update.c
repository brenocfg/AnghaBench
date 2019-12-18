#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {TYPE_2__** crtcs; } ;
struct radeon_device {int disp_priority; scalar_t__ family; TYPE_3__ mode_info; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_4__ {struct drm_display_mode mode; scalar_t__ enabled; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV515 ; 
 int MC_DISP0R_INIT_LAT_MASK ; 
 int MC_DISP0R_INIT_LAT_SHIFT ; 
 int MC_DISP1R_INIT_LAT_MASK ; 
 int MC_DISP1R_INIT_LAT_SHIFT ; 
 int /*<<< orphan*/  MC_MISC_LAT_TIMER ; 
 int RREG32_MC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_MC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_update_display_priority (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_bandwidth_avivo_update (struct radeon_device*) ; 

void rv515_bandwidth_update(struct radeon_device *rdev)
{
	uint32_t tmp;
	struct drm_display_mode *mode0 = NULL;
	struct drm_display_mode *mode1 = NULL;

	radeon_update_display_priority(rdev);

	if (rdev->mode_info.crtcs[0]->base.enabled)
		mode0 = &rdev->mode_info.crtcs[0]->base.mode;
	if (rdev->mode_info.crtcs[1]->base.enabled)
		mode1 = &rdev->mode_info.crtcs[1]->base.mode;
	/*
	 * Set display0/1 priority up in the memory controller for
	 * modes if the user specifies HIGH for displaypriority
	 * option.
	 */
	if ((rdev->disp_priority == 2) &&
	    (rdev->family == CHIP_RV515)) {
		tmp = RREG32_MC(MC_MISC_LAT_TIMER);
		tmp &= ~MC_DISP1R_INIT_LAT_MASK;
		tmp &= ~MC_DISP0R_INIT_LAT_MASK;
		if (mode1)
			tmp |= (1 << MC_DISP1R_INIT_LAT_SHIFT);
		if (mode0)
			tmp |= (1 << MC_DISP0R_INIT_LAT_SHIFT);
		WREG32_MC(MC_MISC_LAT_TIMER, tmp);
	}
	rv515_bandwidth_avivo_update(rdev);
}