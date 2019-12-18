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
struct radeon_device {int flags; TYPE_1__* ddev; } ;
struct TYPE_2__ {scalar_t__ pci_device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_ATI_RADEON_QY ; 
 int RADEON_BUS_BIOS_DIS_ROM ; 
 int /*<<< orphan*/  RADEON_BUS_CNTL ; 
 int RADEON_CRTC2_DISP_REQ_EN_B ; 
 int RADEON_CRTC2_EN ; 
 int /*<<< orphan*/  RADEON_CRTC2_GEN_CNTL ; 
 int RADEON_CRTC_CRT_ON ; 
 int RADEON_CRTC_DISPLAY_DIS ; 
 int RADEON_CRTC_DISP_REQ_EN_B ; 
 int RADEON_CRTC_EN ; 
 int /*<<< orphan*/  RADEON_CRTC_EXT_CNTL ; 
 int RADEON_CRTC_EXT_DISP_EN ; 
 int /*<<< orphan*/  RADEON_CRTC_GEN_CNTL ; 
 int RADEON_CRTC_SYNC_TRISTAT ; 
 int /*<<< orphan*/  RADEON_FP2_GEN_CNTL ; 
 int RADEON_FP2_ON ; 
 int RADEON_IS_PCIE ; 
 int RADEON_SCK_PRESCALE_MASK ; 
 int RADEON_SCK_PRESCALE_SHIFT ; 
 int /*<<< orphan*/  RADEON_SEPROM_CNTL1 ; 
 int RADEON_SINGLE_CRTC ; 
 int /*<<< orphan*/  RADEON_VIPH_CONTROL ; 
 int RADEON_VIPH_EN ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RV370_BUS_BIOS_DIS_ROM ; 
 int /*<<< orphan*/  RV370_BUS_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int radeon_read_bios (struct radeon_device*) ; 

__attribute__((used)) static bool legacy_read_disabled_bios(struct radeon_device *rdev)
{
	uint32_t seprom_cntl1;
	uint32_t viph_control;
	uint32_t bus_cntl;
	uint32_t crtc_gen_cntl;
	uint32_t crtc2_gen_cntl;
	uint32_t crtc_ext_cntl;
	uint32_t fp2_gen_cntl;
	bool r;

	seprom_cntl1 = RREG32(RADEON_SEPROM_CNTL1);
	viph_control = RREG32(RADEON_VIPH_CONTROL);
	if (rdev->flags & RADEON_IS_PCIE)
		bus_cntl = RREG32(RV370_BUS_CNTL);
	else
		bus_cntl = RREG32(RADEON_BUS_CNTL);
	crtc_gen_cntl = RREG32(RADEON_CRTC_GEN_CNTL);
	crtc2_gen_cntl = 0;
	crtc_ext_cntl = RREG32(RADEON_CRTC_EXT_CNTL);
	fp2_gen_cntl = 0;

	if (rdev->ddev->pci_device == PCI_DEVICE_ID_ATI_RADEON_QY) {
		fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);
	}

	if (!(rdev->flags & RADEON_SINGLE_CRTC)) {
		crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL);
	}

	WREG32(RADEON_SEPROM_CNTL1,
	       ((seprom_cntl1 & ~RADEON_SCK_PRESCALE_MASK) |
		(0xc << RADEON_SCK_PRESCALE_SHIFT)));

	/* disable VIP */
	WREG32(RADEON_VIPH_CONTROL, (viph_control & ~RADEON_VIPH_EN));

	/* enable the rom */
	if (rdev->flags & RADEON_IS_PCIE)
		WREG32(RV370_BUS_CNTL, (bus_cntl & ~RV370_BUS_BIOS_DIS_ROM));
	else
		WREG32(RADEON_BUS_CNTL, (bus_cntl & ~RADEON_BUS_BIOS_DIS_ROM));

	/* Turn off mem requests and CRTC for both controllers */
	WREG32(RADEON_CRTC_GEN_CNTL,
	       ((crtc_gen_cntl & ~RADEON_CRTC_EN) |
		(RADEON_CRTC_DISP_REQ_EN_B |
		 RADEON_CRTC_EXT_DISP_EN)));
	if (!(rdev->flags & RADEON_SINGLE_CRTC)) {
		WREG32(RADEON_CRTC2_GEN_CNTL,
		       ((crtc2_gen_cntl & ~RADEON_CRTC2_EN) |
			RADEON_CRTC2_DISP_REQ_EN_B));
	}
	/* Turn off CRTC */
	WREG32(RADEON_CRTC_EXT_CNTL,
	       ((crtc_ext_cntl & ~RADEON_CRTC_CRT_ON) |
		(RADEON_CRTC_SYNC_TRISTAT |
		 RADEON_CRTC_DISPLAY_DIS)));

	if (rdev->ddev->pci_device == PCI_DEVICE_ID_ATI_RADEON_QY) {
		WREG32(RADEON_FP2_GEN_CNTL, (fp2_gen_cntl & ~RADEON_FP2_ON));
	}

	r = radeon_read_bios(rdev);

	/* restore regs */
	WREG32(RADEON_SEPROM_CNTL1, seprom_cntl1);
	WREG32(RADEON_VIPH_CONTROL, viph_control);
	if (rdev->flags & RADEON_IS_PCIE)
		WREG32(RV370_BUS_CNTL, bus_cntl);
	else
		WREG32(RADEON_BUS_CNTL, bus_cntl);
	WREG32(RADEON_CRTC_GEN_CNTL, crtc_gen_cntl);
	if (!(rdev->flags & RADEON_SINGLE_CRTC)) {
		WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);
	}
	WREG32(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl);
	if (rdev->ddev->pci_device == PCI_DEVICE_ID_ATI_RADEON_QY) {
		WREG32(RADEON_FP2_GEN_CNTL, fp2_gen_cntl);
	}
	return r;
}