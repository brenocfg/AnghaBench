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
typedef  int u32 ;
struct radeon_device {int flags; scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_X2 (struct radeon_device*) ; 
 scalar_t__ CHIP_RV770 ; 
 int R600_PCIE_LC_RECONFIG_ARC_MISSING_ESCAPE ; 
 int R600_PCIE_LC_RENEGOTIATE_EN ; 
 int R600_PCIE_LC_RENEGOTIATION_SUPPORT ; 
 int R600_PCIE_LC_UPCONFIGURE_DIS ; 
 int R600_PCIE_LC_UPCONFIGURE_SUPPORT ; 
 int R600_TARGET_AND_CURRENT_PROFILE_INDEX ; 
 int R700_TARGET_AND_CURRENT_PROFILE_INDEX ; 
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int /*<<< orphan*/  RADEON_PCIE_LC_LINK_WIDTH_CNTL ; 
 int RADEON_PCIE_LC_LINK_WIDTH_MASK ; 
 int RADEON_PCIE_LC_LINK_WIDTH_RD_MASK ; 
 int RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X0 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X1 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X12 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X16 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X2 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X4 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X8 ; 
 int RADEON_PCIE_LC_RECONFIG_NOW ; 
 int RREG32 (int) ; 
 int RREG32_PCIE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE_P (int /*<<< orphan*/ ,int) ; 

void r600_set_pcie_lanes(struct radeon_device *rdev, int lanes)
{
	u32 link_width_cntl, mask, target_reg;

	if (rdev->flags & RADEON_IS_IGP)
		return;

	if (!(rdev->flags & RADEON_IS_PCIE))
		return;

	/* x2 cards have a special sequence */
	if (ASIC_IS_X2(rdev))
		return;

	/* FIXME wait for idle */

	switch (lanes) {
	case 0:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X0;
		break;
	case 1:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X1;
		break;
	case 2:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X2;
		break;
	case 4:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X4;
		break;
	case 8:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X8;
		break;
	case 12:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X12;
		break;
	case 16:
	default:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X16;
		break;
	}

	link_width_cntl = RREG32_PCIE_P(RADEON_PCIE_LC_LINK_WIDTH_CNTL);

	if ((link_width_cntl & RADEON_PCIE_LC_LINK_WIDTH_RD_MASK) ==
	    (mask << RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT))
		return;

	if (link_width_cntl & R600_PCIE_LC_UPCONFIGURE_DIS)
		return;

	link_width_cntl &= ~(RADEON_PCIE_LC_LINK_WIDTH_MASK |
			     RADEON_PCIE_LC_RECONFIG_NOW |
			     R600_PCIE_LC_RENEGOTIATE_EN |
			     R600_PCIE_LC_RECONFIG_ARC_MISSING_ESCAPE);
	link_width_cntl |= mask;

	WREG32_PCIE_P(RADEON_PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);

        /* some northbridges can renegotiate the link rather than requiring                                  
         * a complete re-config.                                                                             
         * e.g., AMD 780/790 northbridges (pci ids: 0x5956, 0x5957, 0x5958, etc.)                            
         */
        if (link_width_cntl & R600_PCIE_LC_RENEGOTIATION_SUPPORT)
		link_width_cntl |= R600_PCIE_LC_RENEGOTIATE_EN | R600_PCIE_LC_UPCONFIGURE_SUPPORT;
        else
		link_width_cntl |= R600_PCIE_LC_RECONFIG_ARC_MISSING_ESCAPE;

	WREG32_PCIE_P(RADEON_PCIE_LC_LINK_WIDTH_CNTL, (link_width_cntl |
						       RADEON_PCIE_LC_RECONFIG_NOW));

        if (rdev->family >= CHIP_RV770)
		target_reg = R700_TARGET_AND_CURRENT_PROFILE_INDEX;
        else
		target_reg = R600_TARGET_AND_CURRENT_PROFILE_INDEX;

        /* wait for lane set to complete */
        link_width_cntl = RREG32(target_reg);
        while (link_width_cntl == 0xffffffff)
		link_width_cntl = RREG32(target_reg);

}