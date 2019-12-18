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
typedef  int uint32_t ;
struct radeon_encoder {int devices; } ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int ATOM_DEVICE_CRT1_SUPPORT ; 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
 int ATOM_DEVICE_DFP1_SUPPORT ; 
 int ATOM_DEVICE_DFP2_SUPPORT ; 
 int ATOM_DEVICE_LCD1_SUPPORT ; 
 int ATOM_DEVICE_TV1_SUPPORT ; 
 int /*<<< orphan*/  RADEON_BIOS_5_SCRATCH ; 
 int RADEON_CRT1_CRTC_MASK ; 
 int RADEON_CRT1_CRTC_SHIFT ; 
 int RADEON_CRT2_CRTC_MASK ; 
 int RADEON_CRT2_CRTC_SHIFT ; 
 int RADEON_DFP1_CRTC_MASK ; 
 int RADEON_DFP1_CRTC_SHIFT ; 
 int RADEON_DFP2_CRTC_MASK ; 
 int RADEON_DFP2_CRTC_SHIFT ; 
 int RADEON_LCD1_CRTC_MASK ; 
 int RADEON_LCD1_CRTC_SHIFT ; 
 int RADEON_TV1_CRTC_MASK ; 
 int RADEON_TV1_CRTC_SHIFT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void
radeon_combios_encoder_crtc_scratch_regs(struct drm_encoder *encoder, int crtc)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t bios_5_scratch = RREG32(RADEON_BIOS_5_SCRATCH);

	if (radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) {
		bios_5_scratch &= ~RADEON_TV1_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_TV1_CRTC_SHIFT);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) {
		bios_5_scratch &= ~RADEON_CRT1_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_CRT1_CRTC_SHIFT);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) {
		bios_5_scratch &= ~RADEON_CRT2_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_CRT2_CRTC_SHIFT);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) {
		bios_5_scratch &= ~RADEON_LCD1_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_LCD1_CRTC_SHIFT);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) {
		bios_5_scratch &= ~RADEON_DFP1_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_DFP1_CRTC_SHIFT);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) {
		bios_5_scratch &= ~RADEON_DFP2_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_DFP2_CRTC_SHIFT);
	}
	WREG32(RADEON_BIOS_5_SCRATCH, bios_5_scratch);
}