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
struct radeon_device {int flags; int /*<<< orphan*/ * bios; } ;

/* Variables and functions */
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  cayman_cp_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  cayman_dma_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  cayman_pcie_gart_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r600_blit_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_irq_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_vram_scratch_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_atombios_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_bo_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fence_driver_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gem_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_ib_pool_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_kms_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_vm_manager_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_wb_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  si_rlc_fini (struct radeon_device*) ; 

void cayman_fini(struct radeon_device *rdev)
{
	r600_blit_fini(rdev);
	cayman_cp_fini(rdev);
	cayman_dma_fini(rdev);
	r600_irq_fini(rdev);
	if (rdev->flags & RADEON_IS_IGP)
		si_rlc_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_vm_manager_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_irq_kms_fini(rdev);
	cayman_pcie_gart_fini(rdev);
	r600_vram_scratch_fini(rdev);
	radeon_gem_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kfree(rdev->bios);
	rdev->bios = NULL;
}