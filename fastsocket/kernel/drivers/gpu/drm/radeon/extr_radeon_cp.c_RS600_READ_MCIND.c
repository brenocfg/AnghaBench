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
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int RS600_MC_ADDR_MASK ; 
 int /*<<< orphan*/  RS600_MC_DATA ; 
 int /*<<< orphan*/  RS600_MC_INDEX ; 
 int RS600_MC_IND_CITF_ARB0 ; 

__attribute__((used)) static u32 RS600_READ_MCIND(drm_radeon_private_t *dev_priv, int addr)
{
	u32 ret;
	RADEON_WRITE(RS600_MC_INDEX, ((addr & RS600_MC_ADDR_MASK) |
				      RS600_MC_IND_CITF_ARB0));
	ret = RADEON_READ(RS600_MC_DATA);
	return ret;
}