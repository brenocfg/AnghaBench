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
struct intel_encoder {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct intel_crtc {int cpu_transcoder; struct drm_crtc base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRANSCODER_EDP ; 
 int /*<<< orphan*/  TRANS_CLK_SEL (int) ; 
 int /*<<< orphan*/  TRANS_CLK_SEL_PORT (int) ; 
 struct intel_encoder* intel_ddi_get_crtc_encoder (struct drm_crtc*) ; 
 int intel_ddi_get_encoder_port (struct intel_encoder*) ; 

void intel_ddi_enable_pipe_clock(struct intel_crtc *intel_crtc)
{
	struct drm_crtc *crtc = &intel_crtc->base;
	struct drm_i915_private *dev_priv = crtc->dev->dev_private;
	struct intel_encoder *intel_encoder = intel_ddi_get_crtc_encoder(crtc);
	enum port port = intel_ddi_get_encoder_port(intel_encoder);
	enum transcoder cpu_transcoder = intel_crtc->cpu_transcoder;

	if (cpu_transcoder != TRANSCODER_EDP)
		I915_WRITE(TRANS_CLK_SEL(cpu_transcoder),
			   TRANS_CLK_SEL_PORT(port));
}