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
 int /*<<< orphan*/  RS690_MC_DATA ; 
 int /*<<< orphan*/  RS690_MC_INDEX ; 
 int RS690_MC_INDEX_MASK ; 

__attribute__((used)) static u32 RS690_READ_MCIND(drm_radeon_private_t *dev_priv, int addr)
{
	u32 ret;
	RADEON_WRITE(RS690_MC_INDEX, (addr & RS690_MC_INDEX_MASK));
	ret = RADEON_READ(RS690_MC_DATA);
	RADEON_WRITE(RS690_MC_INDEX, RS690_MC_INDEX_MASK);
	return ret;
}