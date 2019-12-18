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
struct intel_hdmi {int /*<<< orphan*/  has_hdmi_sink; } ;
struct intel_digital_port {int port; struct intel_hdmi hdmi; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; TYPE_1__* dev; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
#define  PORT_B 130 
#define  PORT_C 129 
#define  PORT_D 128 
 int /*<<< orphan*/  POSTING_READ (int) ; 
 int TVIDEO_DIP_CTL (int /*<<< orphan*/ ) ; 
 int VIDEO_DIP_ENABLE ; 
 int VIDEO_DIP_ENABLE_GAMUT ; 
 int VIDEO_DIP_ENABLE_GCP ; 
 int VIDEO_DIP_ENABLE_VENDOR ; 
 int VIDEO_DIP_FREQ_VSYNC ; 
 int VIDEO_DIP_PORT_B ; 
 int VIDEO_DIP_PORT_C ; 
 int VIDEO_DIP_PORT_D ; 
 int VIDEO_DIP_PORT_MASK ; 
 int VIDEO_DIP_SELECT_AVI ; 
 int /*<<< orphan*/  assert_hdmi_port_disabled (struct intel_hdmi*) ; 
 struct intel_digital_port* enc_to_dig_port (struct drm_encoder*) ; 
 int /*<<< orphan*/  intel_hdmi_set_avi_infoframe (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_hdmi_set_spd_infoframe (struct drm_encoder*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibx_set_infoframes(struct drm_encoder *encoder,
			       struct drm_display_mode *adjusted_mode)
{
	struct drm_i915_private *dev_priv = encoder->dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->crtc);
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(encoder);
	struct intel_hdmi *intel_hdmi = &intel_dig_port->hdmi;
	u32 reg = TVIDEO_DIP_CTL(intel_crtc->pipe);
	u32 val = I915_READ(reg);
	u32 port;

	assert_hdmi_port_disabled(intel_hdmi);

	/* See the big comment in g4x_set_infoframes() */
	val |= VIDEO_DIP_SELECT_AVI | VIDEO_DIP_FREQ_VSYNC;

	if (!intel_hdmi->has_hdmi_sink) {
		if (!(val & VIDEO_DIP_ENABLE))
			return;
		val &= ~VIDEO_DIP_ENABLE;
		I915_WRITE(reg, val);
		POSTING_READ(reg);
		return;
	}

	switch (intel_dig_port->port) {
	case PORT_B:
		port = VIDEO_DIP_PORT_B;
		break;
	case PORT_C:
		port = VIDEO_DIP_PORT_C;
		break;
	case PORT_D:
		port = VIDEO_DIP_PORT_D;
		break;
	default:
		BUG();
		return;
	}

	if (port != (val & VIDEO_DIP_PORT_MASK)) {
		if (val & VIDEO_DIP_ENABLE) {
			val &= ~VIDEO_DIP_ENABLE;
			I915_WRITE(reg, val);
			POSTING_READ(reg);
		}
		val &= ~VIDEO_DIP_PORT_MASK;
		val |= port;
	}

	val |= VIDEO_DIP_ENABLE;
	val &= ~(VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		 VIDEO_DIP_ENABLE_GCP);

	I915_WRITE(reg, val);
	POSTING_READ(reg);

	intel_hdmi_set_avi_infoframe(encoder, adjusted_mode);
	intel_hdmi_set_spd_infoframe(encoder);
}