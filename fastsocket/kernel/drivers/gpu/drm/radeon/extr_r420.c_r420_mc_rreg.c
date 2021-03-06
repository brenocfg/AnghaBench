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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0001F8_MC_IND_INDEX ; 
 int /*<<< orphan*/  R_0001FC_MC_IND_DATA ; 
 int /*<<< orphan*/  S_0001F8_MC_IND_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 r420_mc_rreg(struct radeon_device *rdev, u32 reg)
{
	u32 r;

	WREG32(R_0001F8_MC_IND_INDEX, S_0001F8_MC_IND_ADDR(reg));
	r = RREG32(R_0001FC_MC_IND_DATA);
	return r;
}