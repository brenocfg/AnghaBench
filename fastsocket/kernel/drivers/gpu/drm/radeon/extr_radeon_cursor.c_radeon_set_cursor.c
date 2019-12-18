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
typedef  int uint64_t ;
struct radeon_device {scalar_t__ family; } ;
struct radeon_crtc {int legacy_cursor_offset; int legacy_display_base_addr; scalar_t__ crtc_offset; scalar_t__ crtc_id; } ;
struct drm_gem_object {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ AVIVO_D1CUR_SURFACE_ADDRESS ; 
 scalar_t__ CHIP_RV770 ; 
 scalar_t__ EVERGREEN_CUR_SURFACE_ADDRESS ; 
 scalar_t__ EVERGREEN_CUR_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D1CUR_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D2CUR_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ RADEON_CUR_OFFSET ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void radeon_set_cursor(struct drm_crtc *crtc, struct drm_gem_object *obj,
			      uint64_t gpu_addr)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct radeon_device *rdev = crtc->dev->dev_private;

	if (ASIC_IS_DCE4(rdev)) {
		WREG32(EVERGREEN_CUR_SURFACE_ADDRESS_HIGH + radeon_crtc->crtc_offset,
		       upper_32_bits(gpu_addr));
		WREG32(EVERGREEN_CUR_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
		       gpu_addr & 0xffffffff);
	} else if (ASIC_IS_AVIVO(rdev)) {
		if (rdev->family >= CHIP_RV770) {
			if (radeon_crtc->crtc_id)
				WREG32(R700_D2CUR_SURFACE_ADDRESS_HIGH, upper_32_bits(gpu_addr));
			else
				WREG32(R700_D1CUR_SURFACE_ADDRESS_HIGH, upper_32_bits(gpu_addr));
		}
		WREG32(AVIVO_D1CUR_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
		       gpu_addr & 0xffffffff);
	} else {
		radeon_crtc->legacy_cursor_offset = gpu_addr - radeon_crtc->legacy_display_base_addr;
		/* offset is from DISP(2)_BASE_ADDRESS */
		WREG32(RADEON_CUR_OFFSET + radeon_crtc->crtc_offset, radeon_crtc->legacy_cursor_offset);
	}
}