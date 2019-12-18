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
struct TYPE_2__ {int gtt_mtrr; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  MTRR_TYPE_WRCOMB ; 
 scalar_t__ cpu_has_pat ; 
 int mtrr_add (unsigned long,unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
i915_mtrr_setup(struct drm_i915_private *dev_priv, unsigned long base,
		unsigned long size)
{
	dev_priv->mm.gtt_mtrr = -1;

#if defined(CONFIG_X86_PAT)
	if (cpu_has_pat)
		return;
#endif

	/* Set up a WC MTRR for non-PAT systems.  This is more common than
	 * one would think, because the kernel disables PAT on first
	 * generation Core chips because WC PAT gets overridden by a UC
	 * MTRR if present.  Even if a UC MTRR isn't present.
	 */
	dev_priv->mm.gtt_mtrr = mtrr_add(base, size, MTRR_TYPE_WRCOMB, 1);
	if (dev_priv->mm.gtt_mtrr < 0) {
		DRM_INFO("MTRR allocation failed.  Graphics "
			 "performance may suffer.\n");
	}
}