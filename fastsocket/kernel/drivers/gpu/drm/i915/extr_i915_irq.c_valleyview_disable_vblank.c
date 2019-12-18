#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq_lock; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  I915_DISPLAY_PIPE_A_VBLANK_INTERRUPT ; 
 int /*<<< orphan*/  I915_DISPLAY_PIPE_B_VBLANK_INTERRUPT ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_START_VBLANK_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  VLV_IMR ; 
 int /*<<< orphan*/  i915_disable_pipestat (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void valleyview_disable_vblank(struct drm_device *dev, int pipe)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	unsigned long irqflags;
	u32 imr;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	i915_disable_pipestat(dev_priv, pipe,
			      PIPE_START_VBLANK_INTERRUPT_ENABLE);
	imr = I915_READ(VLV_IMR);
	if (pipe == 0)
		imr |= I915_DISPLAY_PIPE_A_VBLANK_INTERRUPT;
	else
		imr |= I915_DISPLAY_PIPE_B_VBLANK_INTERRUPT;
	I915_WRITE(VLV_IMR, imr);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);
}