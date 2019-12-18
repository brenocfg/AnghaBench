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
struct drm_encoder {TYPE_1__* dev; struct drm_crtc* crtc; } ;
struct intel_encoder {int type; struct drm_encoder base; } ;
struct intel_dp {int dummy; } ;
struct intel_crtc {scalar_t__ ddi_pll_sel; } ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,scalar_t__) ; 
 int INTEL_OUTPUT_DISPLAYPORT ; 
 int INTEL_OUTPUT_EDP ; 
 int /*<<< orphan*/  PORT_CLK_SEL (int) ; 
 scalar_t__ PORT_CLK_SEL_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct intel_dp* enc_to_intel_dp (struct drm_encoder*) ; 
 int intel_ddi_get_encoder_port (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_dp_complete_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_start_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_panel_on (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_panel_vdd_off (struct intel_dp*,int) ; 
 int /*<<< orphan*/  ironlake_edp_panel_vdd_on (struct intel_dp*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void intel_ddi_pre_enable(struct intel_encoder *intel_encoder)
{
	struct drm_encoder *encoder = &intel_encoder->base;
	struct drm_crtc *crtc = encoder->crtc;
	struct drm_i915_private *dev_priv = encoder->dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum port port = intel_ddi_get_encoder_port(intel_encoder);
	int type = intel_encoder->type;

	if (type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);
		ironlake_edp_panel_vdd_on(intel_dp);
		ironlake_edp_panel_on(intel_dp);
		ironlake_edp_panel_vdd_off(intel_dp, true);
	}

	WARN_ON(intel_crtc->ddi_pll_sel == PORT_CLK_SEL_NONE);
	I915_WRITE(PORT_CLK_SEL(port), intel_crtc->ddi_pll_sel);

	if (type == INTEL_OUTPUT_DISPLAYPORT || type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);

		intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);
		intel_dp_start_link_train(intel_dp);
		intel_dp_complete_link_train(intel_dp);
	}
}