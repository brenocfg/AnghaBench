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
 int /*<<< orphan*/  R_000070_MC_IND_INDEX ; 
 int /*<<< orphan*/  R_000074_MC_IND_DATA ; 
 int S_000070_MC_IND_ADDR (int) ; 
 int S_000070_MC_IND_CITF_ARB0 (int) ; 
 int S_000070_MC_IND_WR_EN (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void rs600_mc_wreg(struct radeon_device *rdev, uint32_t reg, uint32_t v)
{
	WREG32(R_000070_MC_IND_INDEX, S_000070_MC_IND_ADDR(reg) |
		S_000070_MC_IND_CITF_ARB0(1) | S_000070_MC_IND_WR_EN(1));
	WREG32(R_000074_MC_IND_DATA, v);
}