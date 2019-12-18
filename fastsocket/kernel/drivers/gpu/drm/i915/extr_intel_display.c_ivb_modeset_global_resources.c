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
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/ * pipe_to_crtc_mapping; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int FDI_BC_BIFURCATION_SELECT ; 
 int /*<<< orphan*/  FDI_RX_CTL (size_t) ; 
 int FDI_RX_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 size_t PIPE_B ; 
 size_t PIPE_C ; 
 int /*<<< orphan*/  SOUTH_CHICKEN1 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ivb_modeset_global_resources(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *pipe_B_crtc =
		to_intel_crtc(dev_priv->pipe_to_crtc_mapping[PIPE_B]);
	struct intel_crtc *pipe_C_crtc =
		to_intel_crtc(dev_priv->pipe_to_crtc_mapping[PIPE_C]);
	uint32_t temp;

	/* When everything is off disable fdi C so that we could enable fdi B
	 * with all lanes. XXX: This misses the case where a pipe is not using
	 * any pch resources and so doesn't need any fdi lanes. */
	if (!pipe_B_crtc->base.enabled && !pipe_C_crtc->base.enabled) {
		WARN_ON(I915_READ(FDI_RX_CTL(PIPE_B)) & FDI_RX_ENABLE);
		WARN_ON(I915_READ(FDI_RX_CTL(PIPE_C)) & FDI_RX_ENABLE);

		temp = I915_READ(SOUTH_CHICKEN1);
		temp &= ~FDI_BC_BIFURCATION_SELECT;
		DRM_DEBUG_KMS("disabling fdi C rx\n");
		I915_WRITE(SOUTH_CHICKEN1, temp);
	}
}