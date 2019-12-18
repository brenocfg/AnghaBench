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
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PORT_TO_PIPE (int) ; 
 int /*<<< orphan*/  TV_CTL ; 
 int TV_ENC_ENABLE ; 

__attribute__((used)) static bool
intel_tv_get_hw_state(struct intel_encoder *encoder, enum pipe *pipe)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 tmp = I915_READ(TV_CTL);

	if (!(tmp & TV_ENC_ENABLE))
		return false;

	*pipe = PORT_TO_PIPE(tmp);

	return true;
}