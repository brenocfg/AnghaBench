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

/* Variables and functions */
 unsigned int EVERGREEN_ADDR_SURF_BANK_HEIGHT_1 ; 
 unsigned int EVERGREEN_ADDR_SURF_BANK_HEIGHT_2 ; 
 unsigned int EVERGREEN_ADDR_SURF_BANK_HEIGHT_4 ; 
 unsigned int EVERGREEN_ADDR_SURF_BANK_HEIGHT_8 ; 
 unsigned int EVERGREEN_ADDR_SURF_BANK_WIDTH_1 ; 
 unsigned int EVERGREEN_ADDR_SURF_BANK_WIDTH_2 ; 
 unsigned int EVERGREEN_ADDR_SURF_BANK_WIDTH_4 ; 
 unsigned int EVERGREEN_ADDR_SURF_BANK_WIDTH_8 ; 
 unsigned int EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_1 ; 
 unsigned int EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_2 ; 
 unsigned int EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_4 ; 
 unsigned int EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_8 ; 
 unsigned int RADEON_TILING_EG_BANKH_MASK ; 
 unsigned int RADEON_TILING_EG_BANKH_SHIFT ; 
 unsigned int RADEON_TILING_EG_BANKW_MASK ; 
 unsigned int RADEON_TILING_EG_BANKW_SHIFT ; 
 unsigned int RADEON_TILING_EG_MACRO_TILE_ASPECT_MASK ; 
 unsigned int RADEON_TILING_EG_MACRO_TILE_ASPECT_SHIFT ; 
 unsigned int RADEON_TILING_EG_TILE_SPLIT_MASK ; 
 unsigned int RADEON_TILING_EG_TILE_SPLIT_SHIFT ; 

void evergreen_tiling_fields(unsigned tiling_flags, unsigned *bankw,
			     unsigned *bankh, unsigned *mtaspect,
			     unsigned *tile_split)
{
	*bankw = (tiling_flags >> RADEON_TILING_EG_BANKW_SHIFT) & RADEON_TILING_EG_BANKW_MASK;
	*bankh = (tiling_flags >> RADEON_TILING_EG_BANKH_SHIFT) & RADEON_TILING_EG_BANKH_MASK;
	*mtaspect = (tiling_flags >> RADEON_TILING_EG_MACRO_TILE_ASPECT_SHIFT) & RADEON_TILING_EG_MACRO_TILE_ASPECT_MASK;
	*tile_split = (tiling_flags >> RADEON_TILING_EG_TILE_SPLIT_SHIFT) & RADEON_TILING_EG_TILE_SPLIT_MASK;
	switch (*bankw) {
	default:
	case 1: *bankw = EVERGREEN_ADDR_SURF_BANK_WIDTH_1; break;
	case 2: *bankw = EVERGREEN_ADDR_SURF_BANK_WIDTH_2; break;
	case 4: *bankw = EVERGREEN_ADDR_SURF_BANK_WIDTH_4; break;
	case 8: *bankw = EVERGREEN_ADDR_SURF_BANK_WIDTH_8; break;
	}
	switch (*bankh) {
	default:
	case 1: *bankh = EVERGREEN_ADDR_SURF_BANK_HEIGHT_1; break;
	case 2: *bankh = EVERGREEN_ADDR_SURF_BANK_HEIGHT_2; break;
	case 4: *bankh = EVERGREEN_ADDR_SURF_BANK_HEIGHT_4; break;
	case 8: *bankh = EVERGREEN_ADDR_SURF_BANK_HEIGHT_8; break;
	}
	switch (*mtaspect) {
	default:
	case 1: *mtaspect = EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_1; break;
	case 2: *mtaspect = EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_2; break;
	case 4: *mtaspect = EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_4; break;
	case 8: *mtaspect = EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_8; break;
	}
}