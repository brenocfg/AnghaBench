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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_000078_MC_IND_ADDR ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000078_MC_INDEX ; 
 int /*<<< orphan*/  R_00007C_MC_DATA ; 
 int /*<<< orphan*/  S_000078_MC_IND_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t rs690_mc_rreg(struct radeon_device *rdev, uint32_t reg)
{
	uint32_t r;

	WREG32(R_000078_MC_INDEX, S_000078_MC_IND_ADDR(reg));
	r = RREG32(R_00007C_MC_DATA);
	WREG32(R_000078_MC_INDEX, ~C_000078_MC_IND_ADDR);
	return r;
}