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
struct TYPE_3__ {int vram_is_ddr; int vram_width; scalar_t__ gtt_size; scalar_t__ gtt_base_align; int /*<<< orphan*/  igp_sideport_enabled; } ;
struct radeon_device {TYPE_1__ mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_NB_TOM ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r100_vram_init_sizes (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_combios_sideport_present (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gtt_location (struct radeon_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_update_bandwidth_info (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_vram_location (struct radeon_device*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rs400_gart_adjust_size (struct radeon_device*) ; 

__attribute__((used)) static void rs400_mc_init(struct radeon_device *rdev)
{
	u64 base;

	rs400_gart_adjust_size(rdev);
	rdev->mc.igp_sideport_enabled = radeon_combios_sideport_present(rdev);
	/* DDR for all card after R300 & IGP */
	rdev->mc.vram_is_ddr = true;
	rdev->mc.vram_width = 128;
	r100_vram_init_sizes(rdev);
	base = (RREG32(RADEON_NB_TOM) & 0xffff) << 16;
	radeon_vram_location(rdev, &rdev->mc, base);
	rdev->mc.gtt_base_align = rdev->mc.gtt_size - 1;
	radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
}