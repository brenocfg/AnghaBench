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
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_CNTL ; 
 int RADEON_PCIE_TX_GART_EN ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_END_HI ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_END_LO ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_START_HI ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_START_LO ; 
 int RADEON_PCIE_TX_GART_UNMAPPED_ACCESS_DISCARD ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_gart_table_vram_unpin (struct radeon_device*) ; 

void rv370_pcie_gart_disable(struct radeon_device *rdev)
{
	u32 tmp;

	WREG32_PCIE(RADEON_PCIE_TX_GART_START_LO, 0);
	WREG32_PCIE(RADEON_PCIE_TX_GART_END_LO, 0);
	WREG32_PCIE(RADEON_PCIE_TX_GART_START_HI, 0);
	WREG32_PCIE(RADEON_PCIE_TX_GART_END_HI, 0);
	tmp = RREG32_PCIE(RADEON_PCIE_TX_GART_CNTL);
	tmp |= RADEON_PCIE_TX_GART_UNMAPPED_ACCESS_DISCARD;
	WREG32_PCIE(RADEON_PCIE_TX_GART_CNTL, tmp & ~RADEON_PCIE_TX_GART_EN);
	radeon_gart_table_vram_unpin(rdev);
}