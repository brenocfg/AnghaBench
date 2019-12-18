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
struct TYPE_3__ {int irq_mask; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEIMR ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ironlake_disable_display_irq(drm_i915_private_t *dev_priv, u32 mask)
{
	if ((dev_priv->irq_mask & mask) != mask) {
		dev_priv->irq_mask |= mask;
		I915_WRITE(DEIMR, dev_priv->irq_mask);
		POSTING_READ(DEIMR);
	}
}