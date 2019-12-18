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
struct intel_lvds_encoder {int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ HAS_PCH_CPT (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int LVDS_PORT_EN ; 
 int PORT_TO_PIPE (int) ; 
 int PORT_TO_PIPE_CPT (int) ; 
 struct intel_lvds_encoder* to_lvds_encoder (TYPE_1__*) ; 

__attribute__((used)) static bool intel_lvds_get_hw_state(struct intel_encoder *encoder,
				    enum pipe *pipe)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	u32 tmp;

	tmp = I915_READ(lvds_encoder->reg);

	if (!(tmp & LVDS_PORT_EN))
		return false;

	if (HAS_PCH_CPT(dev))
		*pipe = PORT_TO_PIPE_CPT(tmp);
	else
		*pipe = PORT_TO_PIPE(tmp);

	return true;
}