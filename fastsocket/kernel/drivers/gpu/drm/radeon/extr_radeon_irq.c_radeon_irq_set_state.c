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
struct drm_device {scalar_t__ irq_enabled; TYPE_1__* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_enable_reg; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_GEN_INT_CNTL ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radeon_irq_set_state(struct drm_device *dev, u32 mask, int state)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;

	if (state)
		dev_priv->irq_enable_reg |= mask;
	else
		dev_priv->irq_enable_reg &= ~mask;

	if (dev->irq_enabled)
		RADEON_WRITE(RADEON_GEN_INT_CNTL, dev_priv->irq_enable_reg);
}