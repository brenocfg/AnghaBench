#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ aper_size; scalar_t__ visible_vram_size; int real_vram_size; scalar_t__ mc_vram_size; int /*<<< orphan*/  aper_base; } ;
struct radeon_device {int flags; TYPE_1__ mc; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CONFIG_APER_SIZE ; 
 int /*<<< orphan*/  RADEON_CONFIG_MEMSIZE ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  RADEON_NB_TOM ; 
 void* RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r100_get_accessible_vram (struct radeon_device*) ; 

void r100_vram_init_sizes(struct radeon_device *rdev)
{
	u64 config_aper_size;

	/* work out accessible VRAM */
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	rdev->mc.visible_vram_size = r100_get_accessible_vram(rdev);
	/* FIXME we don't use the second aperture yet when we could use it */
	if (rdev->mc.visible_vram_size > rdev->mc.aper_size)
		rdev->mc.visible_vram_size = rdev->mc.aper_size;
	config_aper_size = RREG32(RADEON_CONFIG_APER_SIZE);
	if (rdev->flags & RADEON_IS_IGP) {
		uint32_t tom;
		/* read NB_TOM to get the amount of ram stolen for the GPU */
		tom = RREG32(RADEON_NB_TOM);
		rdev->mc.real_vram_size = (((tom >> 16) - (tom & 0xffff) + 1) << 16);
		WREG32(RADEON_CONFIG_MEMSIZE, rdev->mc.real_vram_size);
		rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	} else {
		rdev->mc.real_vram_size = RREG32(RADEON_CONFIG_MEMSIZE);
		/* Some production boards of m6 will report 0
		 * if it's 8 MB
		 */
		if (rdev->mc.real_vram_size == 0) {
			rdev->mc.real_vram_size = 8192 * 1024;
			WREG32(RADEON_CONFIG_MEMSIZE, rdev->mc.real_vram_size);
		}
		/* Fix for RN50, M6, M7 with 8/16/32(??) MBs of VRAM - 
		 * Novell bug 204882 + along with lots of ubuntu ones
		 */
		if (rdev->mc.aper_size > config_aper_size)
			config_aper_size = rdev->mc.aper_size;

		if (config_aper_size > rdev->mc.real_vram_size)
			rdev->mc.mc_vram_size = config_aper_size;
		else
			rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	}
}