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
typedef  int uint32_t ;
struct radeon_device {int num_crtc; scalar_t__ family; TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ subsystem_vendor; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int AVIVO_CRTC_EN ; 
 scalar_t__ AVIVO_D1CRTC_CONTROL ; 
 scalar_t__ AVIVO_D2CRTC_CONTROL ; 
 scalar_t__ CHIP_R600 ; 
 scalar_t__ EVERGREEN_CRTC0_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC1_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC2_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC3_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC4_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC5_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC_CONTROL ; 
 int EVERGREEN_CRTC_MASTER_EN ; 
 scalar_t__ PCI_VENDOR_ID_APPLE ; 
 scalar_t__ R600_CONFIG_MEMSIZE ; 
 scalar_t__ RADEON_CONFIG_MEMSIZE ; 
 scalar_t__ RADEON_CRTC2_GEN_CNTL ; 
 int RADEON_CRTC_EN ; 
 scalar_t__ RADEON_CRTC_GEN_CNTL ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ efi_enabled ; 

bool radeon_card_posted(struct radeon_device *rdev)
{
	uint32_t reg;

	if (efi_enabled && rdev->pdev->subsystem_vendor == PCI_VENDOR_ID_APPLE)
		return false;

	/* first check CRTCs */
	if (ASIC_IS_DCE4(rdev)) {
		reg = RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET) |
			RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET);
			if (rdev->num_crtc >= 4) {
				reg |= RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET) |
					RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET);
			}
			if (rdev->num_crtc >= 6) {
				reg |= RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET) |
					RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET);
			}
		if (reg & EVERGREEN_CRTC_MASTER_EN)
			return true;
	} else if (ASIC_IS_AVIVO(rdev)) {
		reg = RREG32(AVIVO_D1CRTC_CONTROL) |
		      RREG32(AVIVO_D2CRTC_CONTROL);
		if (reg & AVIVO_CRTC_EN) {
			return true;
		}
	} else {
		reg = RREG32(RADEON_CRTC_GEN_CNTL) |
		      RREG32(RADEON_CRTC2_GEN_CNTL);
		if (reg & RADEON_CRTC_EN) {
			return true;
		}
	}

	/* then check MEM_SIZE, in case the crtcs are off */
	if (rdev->family >= CHIP_R600)
		reg = RREG32(R600_CONFIG_MEMSIZE);
	else
		reg = RREG32(RADEON_CONFIG_MEMSIZE);

	if (reg)
		return true;

	return false;

}