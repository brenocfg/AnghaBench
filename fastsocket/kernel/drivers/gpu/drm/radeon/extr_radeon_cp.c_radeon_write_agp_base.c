#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_R200 ; 
 int CHIP_R600 ; 
 int CHIP_RS400 ; 
 int CHIP_RS480 ; 
 int CHIP_RS600 ; 
 int CHIP_RS690 ; 
 int CHIP_RS740 ; 
 int CHIP_RV515 ; 
 int CHIP_RV770 ; 
 int /*<<< orphan*/  R500_WRITE_MCIND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  R520_MC_AGP_BASE ; 
 int /*<<< orphan*/  R520_MC_AGP_BASE_2 ; 
 int /*<<< orphan*/  R600_MC_VM_AGP_BASE ; 
 int /*<<< orphan*/  R700_MC_VM_AGP_BASE ; 
 int /*<<< orphan*/  RADEON_AGP_BASE ; 
 int /*<<< orphan*/  RADEON_AGP_BASE_2 ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RS480_AGP_BASE_2 ; 
 int /*<<< orphan*/  RS600_AGP_BASE ; 
 int /*<<< orphan*/  RS600_AGP_BASE_2 ; 
 int /*<<< orphan*/  RS600_WRITE_MCIND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RS690_MC_AGP_BASE ; 
 int /*<<< orphan*/  RS690_MC_AGP_BASE_2 ; 
 int /*<<< orphan*/  RS690_WRITE_MCIND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RV515_MC_AGP_BASE ; 
 int /*<<< orphan*/  RV515_MC_AGP_BASE_2 ; 
 int upper_32_bits (int) ; 

void radeon_write_agp_base(drm_radeon_private_t *dev_priv, u64 agp_base)
{
	u32 agp_base_hi = upper_32_bits(agp_base);
	u32 agp_base_lo = agp_base & 0xffffffff;
	u32 r6xx_agp_base = (agp_base >> 22) & 0x3ffff;

	/* R6xx/R7xx must be aligned to a 4MB boundary */
	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770)
		RADEON_WRITE(R700_MC_VM_AGP_BASE, r6xx_agp_base);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
		RADEON_WRITE(R600_MC_VM_AGP_BASE, r6xx_agp_base);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV515) {
		R500_WRITE_MCIND(RV515_MC_AGP_BASE, agp_base_lo);
		R500_WRITE_MCIND(RV515_MC_AGP_BASE_2, agp_base_hi);
	} else if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS690) ||
		 ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS740)) {
		RS690_WRITE_MCIND(RS690_MC_AGP_BASE, agp_base_lo);
		RS690_WRITE_MCIND(RS690_MC_AGP_BASE_2, agp_base_hi);
	} else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS600) {
		RS600_WRITE_MCIND(RS600_AGP_BASE, agp_base_lo);
		RS600_WRITE_MCIND(RS600_AGP_BASE_2, agp_base_hi);
	} else if ((dev_priv->flags & RADEON_FAMILY_MASK) > CHIP_RV515) {
		R500_WRITE_MCIND(R520_MC_AGP_BASE, agp_base_lo);
		R500_WRITE_MCIND(R520_MC_AGP_BASE_2, agp_base_hi);
	} else if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS400) ||
		   ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS480)) {
		RADEON_WRITE(RADEON_AGP_BASE, agp_base_lo);
		RADEON_WRITE(RS480_AGP_BASE_2, agp_base_hi);
	} else {
		RADEON_WRITE(RADEON_AGP_BASE, agp_base_lo);
		if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R200)
			RADEON_WRITE(RADEON_AGP_BASE_2, agp_base_hi);
	}
}