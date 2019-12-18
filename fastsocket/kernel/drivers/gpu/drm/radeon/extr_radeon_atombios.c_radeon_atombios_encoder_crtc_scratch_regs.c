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
struct radeon_device {scalar_t__ family; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int ATOM_DEVICE_CRT1_SUPPORT ; 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_DFP1_SUPPORT ; 
 int ATOM_DEVICE_DFP2_SUPPORT ; 
 int ATOM_DEVICE_DFP3_SUPPORT ; 
 int ATOM_DEVICE_LCD1_SUPPORT ; 
 int ATOM_DEVICE_TV1_SUPPORT ; 
 int ATOM_S3_CRT1_CRTC_ACTIVE ; 
 int ATOM_S3_CRT2_CRTC_ACTIVE ; 
 int ATOM_S3_CV_CRTC_ACTIVE ; 
 int ATOM_S3_DFP1_CRTC_ACTIVE ; 
 int ATOM_S3_DFP2_CRTC_ACTIVE ; 
 int ATOM_S3_DFP3_CRTC_ACTIVE ; 
 int ATOM_S3_LCD1_CRTC_ACTIVE ; 
 int ATOM_S3_TV1_CRTC_ACTIVE ; 
 scalar_t__ CHIP_R600 ; 
 int /*<<< orphan*/  R600_BIOS_3_SCRATCH ; 
 int /*<<< orphan*/  RADEON_BIOS_3_SCRATCH ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void
radeon_atombios_encoder_crtc_scratch_regs(struct drm_encoder *encoder, int crtc)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t bios_3_scratch;

	if (ASIC_IS_DCE4(rdev))
		return;

	if (rdev->family >= CHIP_R600)
		bios_3_scratch = RREG32(R600_BIOS_3_SCRATCH);
	else
		bios_3_scratch = RREG32(RADEON_BIOS_3_SCRATCH);

	if (radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) {
		bios_3_scratch &= ~ATOM_S3_TV1_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 18);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_CV_SUPPORT) {
		bios_3_scratch &= ~ATOM_S3_CV_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 24);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) {
		bios_3_scratch &= ~ATOM_S3_CRT1_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 16);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) {
		bios_3_scratch &= ~ATOM_S3_CRT2_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 20);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) {
		bios_3_scratch &= ~ATOM_S3_LCD1_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 17);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) {
		bios_3_scratch &= ~ATOM_S3_DFP1_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 19);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) {
		bios_3_scratch &= ~ATOM_S3_DFP2_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 23);
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP3_SUPPORT) {
		bios_3_scratch &= ~ATOM_S3_DFP3_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 25);
	}

	if (rdev->family >= CHIP_R600)
		WREG32(R600_BIOS_3_SCRATCH, bios_3_scratch);
	else
		WREG32(RADEON_BIOS_3_SCRATCH, bios_3_scratch);
}