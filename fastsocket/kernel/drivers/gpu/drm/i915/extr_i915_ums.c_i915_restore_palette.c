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
struct TYPE_2__ {int /*<<< orphan*/ * save_palette_b; int /*<<< orphan*/ * save_palette_a; } ;
struct drm_i915_private {TYPE_1__ regfile; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int /*<<< orphan*/  I915_WRITE (unsigned long,int /*<<< orphan*/ ) ; 
 int PIPE_A ; 
 unsigned long _LGC_PALETTE_A ; 
 unsigned long _LGC_PALETTE_B ; 
 unsigned long _PALETTE_A ; 
 unsigned long _PALETTE_B ; 
 int /*<<< orphan*/  i915_pipe_enabled (struct drm_device*,int) ; 

__attribute__((used)) static void i915_restore_palette(struct drm_device *dev, enum pipe pipe)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long reg = (pipe == PIPE_A ? _PALETTE_A : _PALETTE_B);
	u32 *array;
	int i;

	if (!i915_pipe_enabled(dev, pipe))
		return;

	if (HAS_PCH_SPLIT(dev))
		reg = (pipe == PIPE_A) ? _LGC_PALETTE_A : _LGC_PALETTE_B;

	if (pipe == PIPE_A)
		array = dev_priv->regfile.save_palette_a;
	else
		array = dev_priv->regfile.save_palette_b;

	for (i = 0; i < 256; i++)
		I915_WRITE(reg + (i << 2), array[i]);
}