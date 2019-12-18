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
typedef  scalar_t__ uint32_t ;
struct radeon_encoder_atom_dig {TYPE_1__* afmt; } ;
struct radeon_encoder {int encoder_id; struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_device {int /*<<< orphan*/  dev; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_2__ {int enabled; int /*<<< orphan*/  id; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE2 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE3 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 int /*<<< orphan*/  AVIVO_LVTMA_CNTL ; 
 int /*<<< orphan*/  AVIVO_LVTMA_CNTL_HDMI_EN ; 
 int /*<<< orphan*/  AVIVO_TMDSA_CNTL ; 
 int /*<<< orphan*/  AVIVO_TMDSA_CNTL_HDMI_EN ; 
 int /*<<< orphan*/  DDIA_CNTL ; 
 int /*<<< orphan*/  DDIA_HDMI_EN ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,int) ; 
#define  ENCODER_OBJECT_ID_INTERNAL_DDI 131 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 130 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 128 
 scalar_t__ HDMI0_CONTROL ; 
 int /*<<< orphan*/  HDMI0_ERROR_ACK ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  radeon_irq_kms_disable_afmt (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void r600_hdmi_disable(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	uint32_t offset;

	if (ASIC_IS_DCE6(rdev))
		return;

	/* Called for ATOM_ENCODER_MODE_HDMI only */
	if (!dig || !dig->afmt) {
		return;
	}
	if (!dig->afmt->enabled)
		return;
	offset = dig->afmt->offset;

	DRM_DEBUG("Disabling HDMI interface @ 0x%04X for encoder 0x%x\n",
		  offset, radeon_encoder->encoder_id);

	/* disable irq */
	radeon_irq_kms_disable_afmt(rdev, dig->afmt->id);

	/* Older chipsets not handled by AtomBIOS */
	if (ASIC_IS_DCE2(rdev) && !ASIC_IS_DCE3(rdev)) {
		switch (radeon_encoder->encoder_id) {
		case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
			WREG32_P(AVIVO_TMDSA_CNTL, 0,
				 ~AVIVO_TMDSA_CNTL_HDMI_EN);
			break;
		case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
			WREG32_P(AVIVO_LVTMA_CNTL, 0,
				 ~AVIVO_LVTMA_CNTL_HDMI_EN);
			break;
		case ENCODER_OBJECT_ID_INTERNAL_DDI:
			WREG32_P(DDIA_CNTL, 0, ~DDIA_HDMI_EN);
			break;
		case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
			break;
		default:
			dev_err(rdev->dev, "Invalid encoder for HDMI: 0x%X\n",
				radeon_encoder->encoder_id);
			break;
		}
		WREG32(HDMI0_CONTROL + offset, HDMI0_ERROR_ACK);
	}

	dig->afmt->enabled = false;
}