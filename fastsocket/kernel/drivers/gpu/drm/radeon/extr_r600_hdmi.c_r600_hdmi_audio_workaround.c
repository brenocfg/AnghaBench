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
typedef  scalar_t__ u32 ;
struct radeon_encoder_atom_dig {TYPE_1__* afmt; } ;
struct radeon_encoder {struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ HDMI0_AUDIO_PACKET_CONTROL ; 
 scalar_t__ HDMI0_AUDIO_TEST_EN ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ r600_hdmi_is_audio_buffer_filled (struct drm_encoder*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void r600_hdmi_audio_workaround(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	uint32_t offset = dig->afmt->offset;
	bool hdmi_audio_workaround = false; /* FIXME */
	u32 value;

	if (!hdmi_audio_workaround ||
	    r600_hdmi_is_audio_buffer_filled(encoder))
		value = 0; /* disable workaround */
	else
		value = HDMI0_AUDIO_TEST_EN; /* enable workaround */
	WREG32_P(HDMI0_AUDIO_PACKET_CONTROL + offset,
		 value, ~HDMI0_AUDIO_TEST_EN);
}