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
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {int irq_enable_mask; } ;
typedef  TYPE_1__ drm_via_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int VIA_IRQ_VBLANK_ENABLE ; 
 int VIA_READ (int /*<<< orphan*/ ) ; 
 int VIA_READ8 (int) ; 
 int /*<<< orphan*/  VIA_REG_INTERRUPT ; 
 int /*<<< orphan*/  VIA_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VIA_WRITE8 (int,int) ; 

void via_driver_irq_uninstall(struct drm_device *dev)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
	u32 status;

	DRM_DEBUG("\n");
	if (dev_priv) {

		/* Some more magic, oh for some data sheets ! */

		VIA_WRITE8(0x83d4, 0x11);
		VIA_WRITE8(0x83d5, VIA_READ8(0x83d5) & ~0x30);

		status = VIA_READ(VIA_REG_INTERRUPT);
		VIA_WRITE(VIA_REG_INTERRUPT, status &
			  ~(VIA_IRQ_VBLANK_ENABLE | dev_priv->irq_enable_mask));
	}
}