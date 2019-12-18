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
typedef  int uint32_t ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_RN50 (struct radeon_device*) ; 
 scalar_t__ CHIP_R300 ; 
 scalar_t__ CHIP_RS200 ; 
 scalar_t__ CHIP_RV280 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int,int) ; 
 int R200_SURF_TILE_COLOR_MACRO ; 
 int R200_SURF_TILE_COLOR_MICRO ; 
 int R300_SURF_TILE_MACRO ; 
 int R300_SURF_TILE_MICRO ; 
 scalar_t__ RADEON_SURFACE0_INFO ; 
 scalar_t__ RADEON_SURFACE0_LOWER_BOUND ; 
 scalar_t__ RADEON_SURFACE0_UPPER_BOUND ; 
 int RADEON_SURF_AP0_SWP_16BPP ; 
 int RADEON_SURF_AP0_SWP_32BPP ; 
 int RADEON_SURF_AP1_SWP_16BPP ; 
 int RADEON_SURF_AP1_SWP_32BPP ; 
 int RADEON_SURF_TILE_COLOR_BOTH ; 
 int RADEON_SURF_TILE_COLOR_MACRO ; 
 int RADEON_TILING_MACRO ; 
 int RADEON_TILING_MICRO ; 
 int RADEON_TILING_SWAP_16BIT ; 
 int RADEON_TILING_SWAP_32BIT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 

int r100_set_surface_reg(struct radeon_device *rdev, int reg,
			 uint32_t tiling_flags, uint32_t pitch,
			 uint32_t offset, uint32_t obj_size)
{
	int surf_index = reg * 16;
	int flags = 0;

	if (rdev->family <= CHIP_RS200) {
		if ((tiling_flags & (RADEON_TILING_MACRO|RADEON_TILING_MICRO))
				 == (RADEON_TILING_MACRO|RADEON_TILING_MICRO))
			flags |= RADEON_SURF_TILE_COLOR_BOTH;
		if (tiling_flags & RADEON_TILING_MACRO)
			flags |= RADEON_SURF_TILE_COLOR_MACRO;
	} else if (rdev->family <= CHIP_RV280) {
		if (tiling_flags & (RADEON_TILING_MACRO))
			flags |= R200_SURF_TILE_COLOR_MACRO;
		if (tiling_flags & RADEON_TILING_MICRO)
			flags |= R200_SURF_TILE_COLOR_MICRO;
	} else {
		if (tiling_flags & RADEON_TILING_MACRO)
			flags |= R300_SURF_TILE_MACRO;
		if (tiling_flags & RADEON_TILING_MICRO)
			flags |= R300_SURF_TILE_MICRO;
	}

	if (tiling_flags & RADEON_TILING_SWAP_16BIT)
		flags |= RADEON_SURF_AP0_SWP_16BPP | RADEON_SURF_AP1_SWP_16BPP;
	if (tiling_flags & RADEON_TILING_SWAP_32BIT)
		flags |= RADEON_SURF_AP0_SWP_32BPP | RADEON_SURF_AP1_SWP_32BPP;

	/* when we aren't tiling the pitch seems to needs to be furtherdivided down. - tested on power5 + rn50 server */
	if (tiling_flags & (RADEON_TILING_SWAP_16BIT | RADEON_TILING_SWAP_32BIT)) {
		if (!(tiling_flags & (RADEON_TILING_MACRO | RADEON_TILING_MICRO)))
			if (ASIC_IS_RN50(rdev))
				pitch /= 16;
	}

	/* r100/r200 divide by 16 */
	if (rdev->family < CHIP_R300)
		flags |= pitch / 16;
	else
		flags |= pitch / 8;


	DRM_DEBUG_KMS("writing surface %d %d %x %x\n", reg, flags, offset, offset+obj_size-1);
	WREG32(RADEON_SURFACE0_INFO + surf_index, flags);
	WREG32(RADEON_SURFACE0_LOWER_BOUND + surf_index, offset);
	WREG32(RADEON_SURFACE0_UPPER_BOUND + surf_index, offset + obj_size - 1);
	return 0;
}