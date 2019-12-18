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
struct rv515_mc_save {int dummy; } ;
struct TYPE_2__ {int vram_start; int vram_end; int gtt_start; int gtt_end; int /*<<< orphan*/  agp_base; int /*<<< orphan*/  real_vram_size; } ;
struct radeon_device {int flags; TYPE_1__ mc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RADEON_IS_AGP ; 
 int /*<<< orphan*/  R_000001_MC_FB_LOCATION ; 
 int /*<<< orphan*/  R_000002_MC_AGP_LOCATION ; 
 int /*<<< orphan*/  R_000003_MC_AGP_BASE ; 
 int /*<<< orphan*/  R_000004_MC_AGP_BASE_2 ; 
 int /*<<< orphan*/  R_0000F8_CONFIG_MEMSIZE ; 
 int /*<<< orphan*/  R_000134_HDP_FB_LOCATION ; 
 int S_000001_MC_FB_START (int) ; 
 int S_000001_MC_FB_TOP (int) ; 
 int S_000002_MC_AGP_START (int) ; 
 int S_000002_MC_AGP_TOP (int) ; 
 int S_000004_AGP_BASE_ADDR_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_000134_HDP_FB_START (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_MC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv515_mc_resume (struct radeon_device*,struct rv515_mc_save*) ; 
 int /*<<< orphan*/  rv515_mc_stop (struct radeon_device*,struct rv515_mc_save*) ; 
 scalar_t__ rv515_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv515_mc_program(struct radeon_device *rdev)
{
	struct rv515_mc_save save;

	/* Stops all mc clients */
	rv515_mc_stop(rdev, &save);

	/* Wait for mc idle */
	if (rv515_mc_wait_for_idle(rdev))
		dev_warn(rdev->dev, "Wait MC idle timeout before updating MC.\n");
	/* Write VRAM size in case we are limiting it */
	WREG32(R_0000F8_CONFIG_MEMSIZE, rdev->mc.real_vram_size);
	/* Program MC, should be a 32bits limited address space */
	WREG32_MC(R_000001_MC_FB_LOCATION,
			S_000001_MC_FB_START(rdev->mc.vram_start >> 16) |
			S_000001_MC_FB_TOP(rdev->mc.vram_end >> 16));
	WREG32(R_000134_HDP_FB_LOCATION,
		S_000134_HDP_FB_START(rdev->mc.vram_start >> 16));
	if (rdev->flags & RADEON_IS_AGP) {
		WREG32_MC(R_000002_MC_AGP_LOCATION,
			S_000002_MC_AGP_START(rdev->mc.gtt_start >> 16) |
			S_000002_MC_AGP_TOP(rdev->mc.gtt_end >> 16));
		WREG32_MC(R_000003_MC_AGP_BASE, lower_32_bits(rdev->mc.agp_base));
		WREG32_MC(R_000004_MC_AGP_BASE_2,
			S_000004_AGP_BASE_ADDR_2(upper_32_bits(rdev->mc.agp_base)));
	} else {
		WREG32_MC(R_000002_MC_AGP_LOCATION, 0xFFFFFFFF);
		WREG32_MC(R_000003_MC_AGP_BASE, 0);
		WREG32_MC(R_000004_MC_AGP_BASE_2, 0);
	}

	rv515_mc_resume(rdev, &save);
}