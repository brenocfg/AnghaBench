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
struct rv515_mc_save {int vga_hdp_control; int vga_render_control; scalar_t__* crtc_enabled; } ;
struct TYPE_2__ {scalar_t__ vram_start; } ;
struct radeon_device {int num_crtc; scalar_t__ family; int usec_timeout; TYPE_1__ mc; } ;

/* Variables and functions */
 int AVIVO_CRTC_DISP_READ_REQUEST_DISABLE ; 
 scalar_t__ AVIVO_D1CRTC_CONTROL ; 
 int AVIVO_D1GRPH_SURFACE_UPDATE_PENDING ; 
 scalar_t__ AVIVO_D1GRPH_UPDATE ; 
 int AVIVO_D1GRPH_UPDATE_LOCK ; 
 scalar_t__ AVIVO_D1MODE_MASTER_UPDATE_LOCK ; 
 scalar_t__ AVIVO_D1MODE_MASTER_UPDATE_MODE ; 
 scalar_t__ CHIP_R600 ; 
 scalar_t__ CHIP_RV770 ; 
 scalar_t__ R600_BIF_FB_EN ; 
 int R600_BLACKOUT_MASK ; 
 scalar_t__ R600_CITF_CNTL ; 
 int R600_FB_READ_EN ; 
 int R600_FB_WRITE_EN ; 
 scalar_t__ R700_D1GRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D1GRPH_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D2GRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D2GRPH_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_MC_CITF_CNTL ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ R_000300_VGA_RENDER_CONTROL ; 
 scalar_t__ R_000310_VGA_MEMORY_BASE_ADDRESS ; 
 scalar_t__ R_000328_VGA_HDP_CONTROL ; 
 scalar_t__ R_006110_D1GRPH_PRIMARY_SURFACE_ADDRESS ; 
 scalar_t__ R_006118_D1GRPH_SECONDARY_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__* crtc_offsets ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int radeon_get_vblank_counter (struct radeon_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int upper_32_bits (scalar_t__) ; 

void rv515_mc_resume(struct radeon_device *rdev, struct rv515_mc_save *save)
{
	u32 tmp, frame_count;
	int i, j;

	/* update crtc base addresses */
	for (i = 0; i < rdev->num_crtc; i++) {
		if (rdev->family >= CHIP_RV770) {
			if (i == 0) {
				WREG32(R700_D1GRPH_PRIMARY_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(rdev->mc.vram_start));
				WREG32(R700_D1GRPH_SECONDARY_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(rdev->mc.vram_start));
			} else {
				WREG32(R700_D2GRPH_PRIMARY_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(rdev->mc.vram_start));
				WREG32(R700_D2GRPH_SECONDARY_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(rdev->mc.vram_start));
			}
		}
		WREG32(R_006110_D1GRPH_PRIMARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)rdev->mc.vram_start);
		WREG32(R_006118_D1GRPH_SECONDARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)rdev->mc.vram_start);
	}
	WREG32(R_000310_VGA_MEMORY_BASE_ADDRESS, (u32)rdev->mc.vram_start);

	/* unlock regs and wait for update */
	for (i = 0; i < rdev->num_crtc; i++) {
		if (save->crtc_enabled[i]) {
			tmp = RREG32(AVIVO_D1MODE_MASTER_UPDATE_MODE + crtc_offsets[i]);
			if ((tmp & 0x3) != 0) {
				tmp &= ~0x3;
				WREG32(AVIVO_D1MODE_MASTER_UPDATE_MODE + crtc_offsets[i], tmp);
			}
			tmp = RREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i]);
			if (tmp & AVIVO_D1GRPH_UPDATE_LOCK) {
				tmp &= ~AVIVO_D1GRPH_UPDATE_LOCK;
				WREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i], tmp);
			}
			tmp = RREG32(AVIVO_D1MODE_MASTER_UPDATE_LOCK + crtc_offsets[i]);
			if (tmp & 1) {
				tmp &= ~1;
				WREG32(AVIVO_D1MODE_MASTER_UPDATE_LOCK + crtc_offsets[i], tmp);
			}
			for (j = 0; j < rdev->usec_timeout; j++) {
				tmp = RREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i]);
				if ((tmp & AVIVO_D1GRPH_SURFACE_UPDATE_PENDING) == 0)
					break;
				udelay(1);
			}
		}
	}

	if (rdev->family >= CHIP_R600) {
		/* unblackout the MC */
		if (rdev->family >= CHIP_RV770)
			tmp = RREG32(R700_MC_CITF_CNTL);
		else
			tmp = RREG32(R600_CITF_CNTL);
		tmp &= ~R600_BLACKOUT_MASK;
		if (rdev->family >= CHIP_RV770)
			WREG32(R700_MC_CITF_CNTL, tmp);
		else
			WREG32(R600_CITF_CNTL, tmp);
		/* allow CPU access */
		WREG32(R600_BIF_FB_EN, R600_FB_READ_EN | R600_FB_WRITE_EN);
	}

	for (i = 0; i < rdev->num_crtc; i++) {
		if (save->crtc_enabled[i]) {
			tmp = RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]);
			tmp &= ~AVIVO_CRTC_DISP_READ_REQUEST_DISABLE;
			WREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i], tmp);
			/* wait for the next frame */
			frame_count = radeon_get_vblank_counter(rdev, i);
			for (j = 0; j < rdev->usec_timeout; j++) {
				if (radeon_get_vblank_counter(rdev, i) != frame_count)
					break;
				udelay(1);
			}
		}
	}
	/* Unlock vga access */
	WREG32(R_000328_VGA_HDP_CONTROL, save->vga_hdp_control);
	mdelay(1);
	WREG32(R_000300_VGA_RENDER_CONTROL, save->vga_render_control);
}