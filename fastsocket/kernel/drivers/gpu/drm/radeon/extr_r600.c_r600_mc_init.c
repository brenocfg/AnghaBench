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
typedef  int u32 ;
struct TYPE_2__ {int vram_is_ddr; int vram_width; int /*<<< orphan*/  igp_sideport_enabled; int /*<<< orphan*/  aper_size; int /*<<< orphan*/  visible_vram_size; void* real_vram_size; void* mc_vram_size; int /*<<< orphan*/  aper_base; } ;
struct radeon_device {int flags; TYPE_1__ mc; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int CHANSIZE_MASK ; 
 int CHANSIZE_OVERRIDE ; 
 int /*<<< orphan*/  CHMAP ; 
 int /*<<< orphan*/  CONFIG_MEMSIZE ; 
 int NOOFCHAN_MASK ; 
 int NOOFCHAN_SHIFT ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  RAMCFG ; 
 void* RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_vram_gtt_location (struct radeon_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_atombios_sideport_present (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_update_bandwidth_info (struct radeon_device*) ; 
 int /*<<< orphan*/  rs690_pm_info (struct radeon_device*) ; 

__attribute__((used)) static int r600_mc_init(struct radeon_device *rdev)
{
	u32 tmp;
	int chansize, numchan;

	/* Get VRAM informations */
	rdev->mc.vram_is_ddr = true;
	tmp = RREG32(RAMCFG);
	if (tmp & CHANSIZE_OVERRIDE) {
		chansize = 16;
	} else if (tmp & CHANSIZE_MASK) {
		chansize = 64;
	} else {
		chansize = 32;
	}
	tmp = RREG32(CHMAP);
	switch ((tmp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) {
	case 0:
	default:
		numchan = 1;
		break;
	case 1:
		numchan = 2;
		break;
	case 2:
		numchan = 4;
		break;
	case 3:
		numchan = 8;
		break;
	}
	rdev->mc.vram_width = numchan * chansize;
	/* Could aper size report 0 ? */
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	/* Setup GPU memory space */
	rdev->mc.mc_vram_size = RREG32(CONFIG_MEMSIZE);
	rdev->mc.real_vram_size = RREG32(CONFIG_MEMSIZE);
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	r600_vram_gtt_location(rdev, &rdev->mc);

	if (rdev->flags & RADEON_IS_IGP) {
		rs690_pm_info(rdev);
		rdev->mc.igp_sideport_enabled = radeon_atombios_sideport_present(rdev);
	}
	radeon_update_bandwidth_info(rdev);
	return 0;
}