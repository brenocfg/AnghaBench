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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ gfx_hws_cpu_addr; } ;
struct drm_i915_private {TYPE_1__ dri1; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ I915_NEED_GFX_HWS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LP_RING (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_read_status_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static inline u32
intel_read_legacy_status_page(struct drm_i915_private *dev_priv, int reg)
{
	if (I915_NEED_GFX_HWS(dev_priv->dev))
		return ioread32(dev_priv->dri1.gfx_hws_cpu_addr + reg);
	else
		return intel_read_status_page(LP_RING(dev_priv), reg);
}