#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_BUF_CTL (int) ; 
 int DDI_BUF_IS_IDLE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_name (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void intel_wait_ddi_buf_idle(struct drm_i915_private *dev_priv,
				    enum port port)
{
	uint32_t reg = DDI_BUF_CTL(port);
	int i;

	for (i = 0; i < 8; i++) {
		udelay(1);
		if (I915_READ(reg) & DDI_BUF_IS_IDLE)
			return;
	}
	DRM_ERROR("Timeout waiting for DDI BUF %c idle bit\n", port_name(port));
}