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
 int /*<<< orphan*/  RADEON_PCIE_DATA ; 
 int /*<<< orphan*/  RADEON_PCIE_INDEX ; 
 int /*<<< orphan*/  RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 RADEON_READ_PCIE(drm_radeon_private_t *dev_priv, int addr)
{
	RADEON_WRITE8(RADEON_PCIE_INDEX, addr & 0xff);
	return RADEON_READ(RADEON_PCIE_DATA);
}