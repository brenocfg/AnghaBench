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
typedef  int u32 ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dvo_reg; } ;
struct intel_dvo {TYPE_1__ dev; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DVO_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PORT_TO_PIPE (int) ; 
 struct intel_dvo* enc_to_intel_dvo (TYPE_2__*) ; 

__attribute__((used)) static bool intel_dvo_get_hw_state(struct intel_encoder *encoder,
				   enum pipe *pipe)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_dvo *intel_dvo = enc_to_intel_dvo(&encoder->base);
	u32 tmp;

	tmp = I915_READ(intel_dvo->dev.dvo_reg);

	if (!(tmp & DVO_ENABLE))
		return false;

	*pipe = PORT_TO_PIPE(tmp);

	return true;
}