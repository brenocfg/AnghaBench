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
typedef  int u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;
struct radeon_crtc {int crtc_id; TYPE_1__ base; scalar_t__ crtc_offset; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE5 (struct radeon_device*) ; 
 scalar_t__ DC_LB_MEMORY_SPLIT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 

__attribute__((used)) static u32 evergreen_line_buffer_adjust(struct radeon_device *rdev,
					struct radeon_crtc *radeon_crtc,
					struct drm_display_mode *mode,
					struct drm_display_mode *other_mode)
{
	u32 tmp;
	/*
	 * Line Buffer Setup
	 * There are 3 line buffers, each one shared by 2 display controllers.
	 * DC_LB_MEMORY_SPLIT controls how that line buffer is shared between
	 * the display controllers.  The paritioning is done via one of four
	 * preset allocations specified in bits 2:0:
	 * first display controller
	 *  0 - first half of lb (3840 * 2)
	 *  1 - first 3/4 of lb (5760 * 2)
	 *  2 - whole lb (7680 * 2), other crtc must be disabled
	 *  3 - first 1/4 of lb (1920 * 2)
	 * second display controller
	 *  4 - second half of lb (3840 * 2)
	 *  5 - second 3/4 of lb (5760 * 2)
	 *  6 - whole lb (7680 * 2), other crtc must be disabled
	 *  7 - last 1/4 of lb (1920 * 2)
	 */
	/* this can get tricky if we have two large displays on a paired group
	 * of crtcs.  Ideally for multiple large displays we'd assign them to
	 * non-linked crtcs for maximum line buffer allocation.
	 */
	if (radeon_crtc->base.enabled && mode) {
		if (other_mode)
			tmp = 0; /* 1/2 */
		else
			tmp = 2; /* whole */
	} else
		tmp = 0;

	/* second controller of the pair uses second half of the lb */
	if (radeon_crtc->crtc_id % 2)
		tmp += 4;
	WREG32(DC_LB_MEMORY_SPLIT + radeon_crtc->crtc_offset, tmp);

	if (radeon_crtc->base.enabled && mode) {
		switch (tmp) {
		case 0:
		case 4:
		default:
			if (ASIC_IS_DCE5(rdev))
				return 4096 * 2;
			else
				return 3840 * 2;
		case 1:
		case 5:
			if (ASIC_IS_DCE5(rdev))
				return 6144 * 2;
			else
				return 5760 * 2;
		case 2:
		case 6:
			if (ASIC_IS_DCE5(rdev))
				return 8192 * 2;
			else
				return 7680 * 2;
		case 3:
		case 7:
			if (ASIC_IS_DCE5(rdev))
				return 2048 * 2;
			else
				return 1920 * 2;
		}
	}

	/* controller not enabled, so no lb used */
	return 0;
}