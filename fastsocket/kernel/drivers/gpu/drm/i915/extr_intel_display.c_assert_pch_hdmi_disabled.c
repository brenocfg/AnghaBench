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
typedef  int u32 ;
struct drm_i915_private {int /*<<< orphan*/  dev; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ HAS_PCH_IBX (int /*<<< orphan*/ ) ; 
 int I915_READ (int) ; 
 int PORT_ENABLE ; 
 int SDVO_PIPE_B_SELECT ; 
 int /*<<< orphan*/  WARN (int,char*,...) ; 
 int /*<<< orphan*/  hdmi_pipe_enabled (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static void assert_pch_hdmi_disabled(struct drm_i915_private *dev_priv,
				     enum pipe pipe, int reg)
{
	u32 val = I915_READ(reg);
	WARN(hdmi_pipe_enabled(dev_priv, pipe, val),
	     "PCH HDMI (0x%08x) enabled on transcoder %c, should be disabled\n",
	     reg, pipe_name(pipe));

	WARN(HAS_PCH_IBX(dev_priv->dev) && (val & PORT_ENABLE) == 0
	     && (val & SDVO_PIPE_B_SELECT),
	     "IBX PCH hdmi port still using transcoder B\n");
}