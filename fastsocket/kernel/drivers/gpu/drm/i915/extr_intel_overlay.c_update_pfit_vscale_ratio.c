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
struct intel_overlay {int pfit_vscale_ratio; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  PFIT_AUTO_RATIOS ; 
 int /*<<< orphan*/  PFIT_CONTROL ; 
 int /*<<< orphan*/  PFIT_PGM_RATIOS ; 
 int PFIT_VERT_SCALE_SHIFT ; 
 int PFIT_VERT_SCALE_SHIFT_965 ; 
 int VERT_AUTO_SCALE ; 

__attribute__((used)) static void update_pfit_vscale_ratio(struct intel_overlay *overlay)
{
	struct drm_device *dev = overlay->dev;
	drm_i915_private_t *dev_priv = dev->dev_private;
	u32 pfit_control = I915_READ(PFIT_CONTROL);
	u32 ratio;

	/* XXX: This is not the same logic as in the xorg driver, but more in
	 * line with the intel documentation for the i965
	 */
	if (INTEL_INFO(dev)->gen >= 4) {
		/* on i965 use the PGM reg to read out the autoscaler values */
		ratio = I915_READ(PFIT_PGM_RATIOS) >> PFIT_VERT_SCALE_SHIFT_965;
	} else {
		if (pfit_control & VERT_AUTO_SCALE)
			ratio = I915_READ(PFIT_AUTO_RATIOS);
		else
			ratio = I915_READ(PFIT_PGM_RATIOS);
		ratio >>= PFIT_VERT_SCALE_SHIFT;
	}

	overlay->pfit_vscale_ratio = ratio;
}