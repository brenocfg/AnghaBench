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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_R600 ; 
 int CHIP_RS600 ; 
 int /*<<< orphan*/  R500_DxMODE_INT_MASK ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RADEON_GEN_INT_CNTL ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_acknowledge_irqs (TYPE_1__*,int /*<<< orphan*/ *) ; 

void radeon_driver_irq_preinstall(struct drm_device * dev)
{
	drm_radeon_private_t *dev_priv =
	    (drm_radeon_private_t *) dev->dev_private;
	u32 dummy;

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
		return;

	/* Disable *all* interrupts */
	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RS600)
		RADEON_WRITE(R500_DxMODE_INT_MASK, 0);
	RADEON_WRITE(RADEON_GEN_INT_CNTL, 0);

	/* Clear bits if they're already high */
	radeon_acknowledge_irqs(dev_priv, &dummy);
}