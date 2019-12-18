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
typedef  int u32 ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_R600 ; 
 int CHIP_RS600 ; 
 int CHIP_RS690 ; 
 int CHIP_RS740 ; 
 int CHIP_RV515 ; 
 int CHIP_RV770 ; 
 int /*<<< orphan*/  R500_WRITE_MCIND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  R520_MC_AGP_LOCATION ; 
 int /*<<< orphan*/  R600_MC_VM_AGP_BOT ; 
 int /*<<< orphan*/  R600_MC_VM_AGP_TOP ; 
 int /*<<< orphan*/  R700_MC_VM_AGP_BOT ; 
 int /*<<< orphan*/  R700_MC_VM_AGP_TOP ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RADEON_MC_AGP_LOCATION ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RS600_MC_AGP_LOCATION ; 
 int /*<<< orphan*/  RS600_WRITE_MCIND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RS690_MC_AGP_LOCATION ; 
 int /*<<< orphan*/  RS690_WRITE_MCIND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RV515_MC_AGP_LOCATION ; 

void radeon_write_agp_location(drm_radeon_private_t *dev_priv, u32 agp_loc)
{
	/*R6xx/R7xx: AGP_TOP and BOT are actually 18 bits each */
	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770) {
		RADEON_WRITE(R700_MC_VM_AGP_BOT, agp_loc & 0xffff); /* FIX ME */
		RADEON_WRITE(R700_MC_VM_AGP_TOP, (agp_loc >> 16) & 0xffff);
	} else if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600) {
		RADEON_WRITE(R600_MC_VM_AGP_BOT, agp_loc & 0xffff); /* FIX ME */
		RADEON_WRITE(R600_MC_VM_AGP_TOP, (agp_loc >> 16) & 0xffff);
	} else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV515)
		R500_WRITE_MCIND(RV515_MC_AGP_LOCATION, agp_loc);
	else if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS690) ||
		 ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS740))
		RS690_WRITE_MCIND(RS690_MC_AGP_LOCATION, agp_loc);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS600)
		RS600_WRITE_MCIND(RS600_MC_AGP_LOCATION, agp_loc);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) > CHIP_RV515)
		R500_WRITE_MCIND(R520_MC_AGP_LOCATION, agp_loc);
	else
		RADEON_WRITE(RADEON_MC_AGP_LOCATION, agp_loc);
}