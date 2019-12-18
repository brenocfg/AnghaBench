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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PA_SC_RASTER_CONFIG ; 
 int RASTER_CONFIG_RB_MAP_0 ; 
 int RASTER_CONFIG_RB_MAP_2 ; 
 int RASTER_CONFIG_RB_MAP_3 ; 
 int TAHITI_RB_BITMAP_WIDTH_PER_SH ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int si_get_rb_disabled (struct radeon_device*,int,int,int) ; 
 int /*<<< orphan*/  si_select_se_sh (struct radeon_device*,int,int) ; 

__attribute__((used)) static void si_setup_rb(struct radeon_device *rdev,
			u32 se_num, u32 sh_per_se,
			u32 max_rb_num)
{
	int i, j;
	u32 data, mask;
	u32 disabled_rbs = 0;
	u32 enabled_rbs = 0;

	for (i = 0; i < se_num; i++) {
		for (j = 0; j < sh_per_se; j++) {
			si_select_se_sh(rdev, i, j);
			data = si_get_rb_disabled(rdev, max_rb_num, se_num, sh_per_se);
			disabled_rbs |= data << ((i * sh_per_se + j) * TAHITI_RB_BITMAP_WIDTH_PER_SH);
		}
	}
	si_select_se_sh(rdev, 0xffffffff, 0xffffffff);

	mask = 1;
	for (i = 0; i < max_rb_num; i++) {
		if (!(disabled_rbs & mask))
			enabled_rbs |= mask;
		mask <<= 1;
	}

	for (i = 0; i < se_num; i++) {
		si_select_se_sh(rdev, i, 0xffffffff);
		data = 0;
		for (j = 0; j < sh_per_se; j++) {
			switch (enabled_rbs & 3) {
			case 1:
				data |= (RASTER_CONFIG_RB_MAP_0 << (i * sh_per_se + j) * 2);
				break;
			case 2:
				data |= (RASTER_CONFIG_RB_MAP_3 << (i * sh_per_se + j) * 2);
				break;
			case 3:
			default:
				data |= (RASTER_CONFIG_RB_MAP_2 << (i * sh_per_se + j) * 2);
				break;
			}
			enabled_rbs >>= 2;
		}
		WREG32(PA_SC_RASTER_CONFIG, data);
	}
	si_select_se_sh(rdev, 0xffffffff, 0xffffffff);
}