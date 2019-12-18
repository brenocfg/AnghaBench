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
struct drm_encoder {TYPE_1__* dev; } ;
struct intel_encoder {int type; struct drm_encoder base; } ;
struct intel_dp {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_BUF_CTL (int) ; 
 int DDI_BUF_CTL_ENABLE ; 
 int /*<<< orphan*/  DP_TP_CTL (int) ; 
 int DP_TP_CTL_ENABLE ; 
 int DP_TP_CTL_LINK_TRAIN_MASK ; 
 int DP_TP_CTL_LINK_TRAIN_PAT1 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_OUTPUT_EDP ; 
 int /*<<< orphan*/  PORT_CLK_SEL (int) ; 
 int PORT_CLK_SEL_NONE ; 
 struct intel_dp* enc_to_intel_dp (struct drm_encoder*) ; 
 int intel_ddi_get_encoder_port (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_wait_ddi_buf_idle (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  ironlake_edp_panel_off (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_panel_vdd_on (struct intel_dp*) ; 

__attribute__((used)) static void intel_ddi_post_disable(struct intel_encoder *intel_encoder)
{
	struct drm_encoder *encoder = &intel_encoder->base;
	struct drm_i915_private *dev_priv = encoder->dev->dev_private;
	enum port port = intel_ddi_get_encoder_port(intel_encoder);
	int type = intel_encoder->type;
	uint32_t val;
	bool wait = false;

	val = I915_READ(DDI_BUF_CTL(port));
	if (val & DDI_BUF_CTL_ENABLE) {
		val &= ~DDI_BUF_CTL_ENABLE;
		I915_WRITE(DDI_BUF_CTL(port), val);
		wait = true;
	}

	val = I915_READ(DP_TP_CTL(port));
	val &= ~(DP_TP_CTL_ENABLE | DP_TP_CTL_LINK_TRAIN_MASK);
	val |= DP_TP_CTL_LINK_TRAIN_PAT1;
	I915_WRITE(DP_TP_CTL(port), val);

	if (wait)
		intel_wait_ddi_buf_idle(dev_priv, port);

	if (type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);
		ironlake_edp_panel_vdd_on(intel_dp);
		ironlake_edp_panel_off(intel_dp);
	}

	I915_WRITE(PORT_CLK_SEL(port), PORT_CLK_SEL_NONE);
}