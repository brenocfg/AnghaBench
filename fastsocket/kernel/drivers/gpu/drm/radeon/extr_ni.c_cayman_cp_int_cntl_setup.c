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
 int /*<<< orphan*/  CP_INT_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRBM_GFX_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void cayman_cp_int_cntl_setup(struct radeon_device *rdev,
			      int ring, u32 cp_int_cntl)
{
	u32 srbm_gfx_cntl = RREG32(SRBM_GFX_CNTL) & ~3;

	WREG32(SRBM_GFX_CNTL, srbm_gfx_cntl | (ring & 3));
	WREG32(CP_INT_CNTL, cp_int_cntl);
}