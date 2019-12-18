#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  enabled; struct drm_device* dev; } ;
struct intel_crtc {int pipe; int fdi_lanes; TYPE_1__ base; } ;
struct drm_i915_private {int num_pipe; TYPE_2__** pipe_to_crtc_mapping; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int FDI_BC_BIFURCATION_SELECT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
#define  PIPE_A 130 
#define  PIPE_B 129 
#define  PIPE_C 128 
 int /*<<< orphan*/  SOUTH_CHICKEN1 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpt_enable_fdi_bc_bifurcation (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (TYPE_2__*) ; 

__attribute__((used)) static bool ironlake_check_fdi_lanes(struct intel_crtc *intel_crtc)
{
	struct drm_device *dev = intel_crtc->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *pipe_B_crtc =
		to_intel_crtc(dev_priv->pipe_to_crtc_mapping[PIPE_B]);

	DRM_DEBUG_KMS("checking fdi config on pipe %i, lanes %i\n",
		      intel_crtc->pipe, intel_crtc->fdi_lanes);
	if (intel_crtc->fdi_lanes > 4) {
		DRM_DEBUG_KMS("invalid fdi lane config on pipe %i: %i lanes\n",
			      intel_crtc->pipe, intel_crtc->fdi_lanes);
		/* Clamp lanes to avoid programming the hw with bogus values. */
		intel_crtc->fdi_lanes = 4;

		return false;
	}

	if (dev_priv->num_pipe == 2)
		return true;

	switch (intel_crtc->pipe) {
	case PIPE_A:
		return true;
	case PIPE_B:
		if (dev_priv->pipe_to_crtc_mapping[PIPE_C]->enabled &&
		    intel_crtc->fdi_lanes > 2) {
			DRM_DEBUG_KMS("invalid shared fdi lane config on pipe %i: %i lanes\n",
				      intel_crtc->pipe, intel_crtc->fdi_lanes);
			/* Clamp lanes to avoid programming the hw with bogus values. */
			intel_crtc->fdi_lanes = 2;

			return false;
		}

		if (intel_crtc->fdi_lanes > 2)
			WARN_ON(I915_READ(SOUTH_CHICKEN1) & FDI_BC_BIFURCATION_SELECT);
		else
			cpt_enable_fdi_bc_bifurcation(dev);

		return true;
	case PIPE_C:
		if (!pipe_B_crtc->base.enabled || pipe_B_crtc->fdi_lanes <= 2) {
			if (intel_crtc->fdi_lanes > 2) {
				DRM_DEBUG_KMS("invalid shared fdi lane config on pipe %i: %i lanes\n",
					      intel_crtc->pipe, intel_crtc->fdi_lanes);
				/* Clamp lanes to avoid programming the hw with bogus values. */
				intel_crtc->fdi_lanes = 2;

				return false;
			}
		} else {
			DRM_DEBUG_KMS("fdi link B uses too many lanes to enable link C\n");
			return false;
		}

		cpt_enable_fdi_bc_bifurcation(dev);

		return true;
	default:
		BUG();
	}
}