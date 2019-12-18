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
struct radeon_device {int flags; int accel_working; int /*<<< orphan*/  ddev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RADEON_IS_PCI ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0007C0_CP_STAT ; 
 int /*<<< orphan*/  R_000E40_RBBM_STATUS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r100_clock_startup (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_pci_gart_disable (struct radeon_device*) ; 
 int r100_startup (struct radeon_device*) ; 
 scalar_t__ radeon_asic_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_combios_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_surface_init (struct radeon_device*) ; 

int r100_resume(struct radeon_device *rdev)
{
	int r;

	/* Make sur GART are not working */
	if (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	/* Resume clock before doing reset */
	r100_clock_startup(rdev);
	/* Reset gpu before posting otherwise ATOM will enter infinite loop */
	if (radeon_asic_reset(rdev)) {
		dev_warn(rdev->dev, "GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	}
	/* post */
	radeon_combios_asic_init(rdev->ddev);
	/* Resume clock after posting */
	r100_clock_startup(rdev);
	/* Initialize surface registers */
	radeon_surface_init(rdev);

	rdev->accel_working = true;
	r = r100_startup(rdev);
	if (r) {
		rdev->accel_working = false;
	}
	return r;
}