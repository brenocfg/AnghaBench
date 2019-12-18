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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r600_audio_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_dma_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_irq_suspend (struct radeon_device*) ; 
 int /*<<< orphan*/  r700_cp_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_wb_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_pcie_gart_disable (struct radeon_device*) ; 

int rv770_suspend(struct radeon_device *rdev)
{
	r600_audio_fini(rdev);
	r700_cp_stop(rdev);
	r600_dma_stop(rdev);
	r600_irq_suspend(rdev);
	radeon_wb_disable(rdev);
	rv770_pcie_gart_disable(rdev);

	return 0;
}