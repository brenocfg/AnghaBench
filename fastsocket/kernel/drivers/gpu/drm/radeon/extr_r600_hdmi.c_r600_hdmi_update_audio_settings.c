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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct radeon_encoder_atom_dig {TYPE_1__* afmt; } ;
struct radeon_encoder {struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct r600_audio {int rate; int bits_per_sample; int status_bits; int /*<<< orphan*/  channels; scalar_t__ category_code; } ;
struct hdmi_audio_infoframe {int /*<<< orphan*/  channels; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int offset; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int AUDIO_STATUS_COPYRIGHT ; 
 int AUDIO_STATUS_EMPHASIS ; 
 int AUDIO_STATUS_NONAUDIO ; 
 int AUDIO_STATUS_PROFESSIONAL ; 
 int AUDIO_STATUS_V ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int HDMI0_60958_0 ; 
 int HDMI0_60958_1 ; 
 int HDMI0_60958_CS_CATEGORY_CODE (scalar_t__) ; 
 int HDMI0_60958_CS_SAMPLING_FREQUENCY (int) ; 
 int HDMI0_60958_CS_WORD_LENGTH (int) ; 
 int HDMI_AUDIO_INFOFRAME_SIZE ; 
 int HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  WREG32_P (int,int,int) ; 
 scalar_t__ hdmi_audio_infoframe_init (struct hdmi_audio_infoframe*) ; 
 scalar_t__ hdmi_audio_infoframe_pack (struct hdmi_audio_infoframe*,int /*<<< orphan*/ *,int) ; 
 struct r600_audio r600_audio_status (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_hdmi_audio_workaround (struct drm_encoder*) ; 
 scalar_t__ r600_hdmi_is_audio_buffer_filled (struct drm_encoder*) ; 
 int /*<<< orphan*/  r600_hdmi_update_audio_infoframe (struct drm_encoder*,int /*<<< orphan*/ *,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void r600_hdmi_update_audio_settings(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	struct r600_audio audio = r600_audio_status(rdev);
	uint8_t buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AUDIO_INFOFRAME_SIZE];
	struct hdmi_audio_infoframe frame;
	uint32_t offset;
	uint32_t iec;
	ssize_t err;

	if (!dig->afmt || !dig->afmt->enabled)
		return;
	offset = dig->afmt->offset;

	DRM_DEBUG("%s with %d channels, %d Hz sampling rate, %d bits per sample,\n",
		 r600_hdmi_is_audio_buffer_filled(encoder) ? "playing" : "stopped",
		  audio.channels, audio.rate, audio.bits_per_sample);
	DRM_DEBUG("0x%02X IEC60958 status bits and 0x%02X category code\n",
		  (int)audio.status_bits, (int)audio.category_code);

	iec = 0;
	if (audio.status_bits & AUDIO_STATUS_PROFESSIONAL)
		iec |= 1 << 0;
	if (audio.status_bits & AUDIO_STATUS_NONAUDIO)
		iec |= 1 << 1;
	if (audio.status_bits & AUDIO_STATUS_COPYRIGHT)
		iec |= 1 << 2;
	if (audio.status_bits & AUDIO_STATUS_EMPHASIS)
		iec |= 1 << 3;

	iec |= HDMI0_60958_CS_CATEGORY_CODE(audio.category_code);

	switch (audio.rate) {
	case 32000:
		iec |= HDMI0_60958_CS_SAMPLING_FREQUENCY(0x3);
		break;
	case 44100:
		iec |= HDMI0_60958_CS_SAMPLING_FREQUENCY(0x0);
		break;
	case 48000:
		iec |= HDMI0_60958_CS_SAMPLING_FREQUENCY(0x2);
		break;
	case 88200:
		iec |= HDMI0_60958_CS_SAMPLING_FREQUENCY(0x8);
		break;
	case 96000:
		iec |= HDMI0_60958_CS_SAMPLING_FREQUENCY(0xa);
		break;
	case 176400:
		iec |= HDMI0_60958_CS_SAMPLING_FREQUENCY(0xc);
		break;
	case 192000:
		iec |= HDMI0_60958_CS_SAMPLING_FREQUENCY(0xe);
		break;
	}

	WREG32(HDMI0_60958_0 + offset, iec);

	iec = 0;
	switch (audio.bits_per_sample) {
	case 16:
		iec |= HDMI0_60958_CS_WORD_LENGTH(0x2);
		break;
	case 20:
		iec |= HDMI0_60958_CS_WORD_LENGTH(0x3);
		break;
	case 24:
		iec |= HDMI0_60958_CS_WORD_LENGTH(0xb);
		break;
	}
	if (audio.status_bits & AUDIO_STATUS_V)
		iec |= 0x5 << 16;
	WREG32_P(HDMI0_60958_1 + offset, iec, ~0x5000f);

	err = hdmi_audio_infoframe_init(&frame);
	if (err < 0) {
		DRM_ERROR("failed to setup audio infoframe\n");
		return;
	}

	frame.channels = audio.channels;

	err = hdmi_audio_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		DRM_ERROR("failed to pack audio infoframe\n");
		return;
	}

	r600_hdmi_update_audio_infoframe(encoder, buffer, sizeof(buffer));
	r600_hdmi_audio_workaround(encoder);
}