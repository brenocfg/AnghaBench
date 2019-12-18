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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_00000F_CP_DYN_CNTL ; 
 int /*<<< orphan*/  R_000011_E2_DYN_CNTL ; 
 int /*<<< orphan*/  R_000013_IDCT_DYN_CNTL ; 
 int S_00000F_CP_FORCEON (int) ; 
 int S_000011_E2_FORCEON (int) ; 
 int S_000013_IDCT_FORCEON (int) ; 
 int /*<<< orphan*/  WREG32_PLL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_atom_set_clock_gating (struct radeon_device*,int) ; 
 int radeon_dynclks ; 

void rv515_clock_startup(struct radeon_device *rdev)
{
	if (radeon_dynclks != -1 && radeon_dynclks)
		radeon_atom_set_clock_gating(rdev, 1);
	/* We need to force on some of the block */
	WREG32_PLL(R_00000F_CP_DYN_CNTL,
		RREG32_PLL(R_00000F_CP_DYN_CNTL) | S_00000F_CP_FORCEON(1));
	WREG32_PLL(R_000011_E2_DYN_CNTL,
		RREG32_PLL(R_000011_E2_DYN_CNTL) | S_000011_E2_FORCEON(1));
	WREG32_PLL(R_000013_IDCT_DYN_CNTL,
		RREG32_PLL(R_000013_IDCT_DYN_CNTL) | S_000013_IDCT_FORCEON(1));
}