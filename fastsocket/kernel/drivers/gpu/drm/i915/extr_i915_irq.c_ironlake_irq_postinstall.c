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
typedef  int u32 ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_3__ {int irq_mask; int gt_irq_mask; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEIER ; 
 int /*<<< orphan*/  DEIIR ; 
 int /*<<< orphan*/  DEIMR ; 
 int DE_AUX_CHANNEL_A ; 
 int DE_GSE ; 
 int DE_MASTER_IRQ_CONTROL ; 
 int DE_PCH_EVENT ; 
 int DE_PCU_EVENT ; 
 int DE_PIPEA_VBLANK ; 
 int DE_PIPEB_VBLANK ; 
 int DE_PLANEA_FLIP_DONE ; 
 int DE_PLANEB_FLIP_DONE ; 
 int GEN6_BLITTER_USER_INTERRUPT ; 
 int GEN6_BSD_USER_INTERRUPT ; 
 int /*<<< orphan*/  GTIER ; 
 int /*<<< orphan*/  GTIIR ; 
 int /*<<< orphan*/  GTIMR ; 
 int GT_BSD_USER_INTERRUPT ; 
 int GT_PIPE_NOTIFY ; 
 int GT_USER_INTERRUPT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 scalar_t__ IS_IRONLAKE_M (struct drm_device*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibx_irq_postinstall (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_enable_display_irq (TYPE_1__*,int) ; 

__attribute__((used)) static int ironlake_irq_postinstall(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	/* enable kind of interrupts always enabled */
	u32 display_mask = DE_MASTER_IRQ_CONTROL | DE_GSE | DE_PCH_EVENT |
			   DE_PLANEA_FLIP_DONE | DE_PLANEB_FLIP_DONE |
			   DE_AUX_CHANNEL_A;
	u32 render_irqs;

	dev_priv->irq_mask = ~display_mask;

	/* should always can generate irq */
	I915_WRITE(DEIIR, I915_READ(DEIIR));
	I915_WRITE(DEIMR, dev_priv->irq_mask);
	I915_WRITE(DEIER, display_mask | DE_PIPEA_VBLANK | DE_PIPEB_VBLANK);
	POSTING_READ(DEIER);

	dev_priv->gt_irq_mask = ~0;

	I915_WRITE(GTIIR, I915_READ(GTIIR));
	I915_WRITE(GTIMR, dev_priv->gt_irq_mask);

	if (IS_GEN6(dev))
		render_irqs =
			GT_USER_INTERRUPT |
			GEN6_BSD_USER_INTERRUPT |
			GEN6_BLITTER_USER_INTERRUPT;
	else
		render_irqs =
			GT_USER_INTERRUPT |
			GT_PIPE_NOTIFY |
			GT_BSD_USER_INTERRUPT;
	I915_WRITE(GTIER, render_irqs);
	POSTING_READ(GTIER);

	ibx_irq_postinstall(dev);

	if (IS_IRONLAKE_M(dev)) {
		/* Clear & enable PCU event interrupts */
		I915_WRITE(DEIIR, DE_PCU_EVENT);
		I915_WRITE(DEIER, I915_READ(DEIER) | DE_PCU_EVENT);
		ironlake_enable_display_irq(dev_priv, DE_PCU_EVENT);
	}

	return 0;
}