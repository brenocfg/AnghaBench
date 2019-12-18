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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_INDEX ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r100_pll_errata_after_data (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_pll_errata_after_index (struct radeon_device*) ; 

uint32_t r100_pll_rreg(struct radeon_device *rdev, uint32_t reg)
{
	uint32_t data;

	WREG8(RADEON_CLOCK_CNTL_INDEX, reg & 0x3f);
	r100_pll_errata_after_index(rdev);
	data = RREG32(RADEON_CLOCK_CNTL_DATA);
	r100_pll_errata_after_data(rdev);
	return data;
}