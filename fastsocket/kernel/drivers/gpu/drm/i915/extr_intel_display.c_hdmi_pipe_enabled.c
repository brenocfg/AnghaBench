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
 scalar_t__ HAS_PCH_CPT (int /*<<< orphan*/ ) ; 
 int PORT_ENABLE ; 
 int PORT_TRANS_SEL_CPT (int) ; 
 int PORT_TRANS_SEL_MASK ; 
 int TRANSCODER (int) ; 
 int TRANSCODER_MASK ; 

__attribute__((used)) static bool hdmi_pipe_enabled(struct drm_i915_private *dev_priv,
			      enum pipe pipe, u32 val)
{
	if ((val & PORT_ENABLE) == 0)
		return false;

	if (HAS_PCH_CPT(dev_priv->dev)) {
		if ((val & PORT_TRANS_SEL_MASK) != PORT_TRANS_SEL_CPT(pipe))
			return false;
	} else {
		if ((val & TRANSCODER_MASK) != TRANSCODER(pipe))
			return false;
	}
	return true;
}