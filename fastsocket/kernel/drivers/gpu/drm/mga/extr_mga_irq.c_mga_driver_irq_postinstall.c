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
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  fence_queue; } ;
typedef  TYPE_1__ drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INIT_WAITQUEUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MGA_IEN ; 
 int /*<<< orphan*/  MGA_SOFTRAPEN ; 
 int /*<<< orphan*/  MGA_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mga_driver_irq_postinstall(struct drm_device *dev)
{
	drm_mga_private_t *dev_priv = (drm_mga_private_t *) dev->dev_private;

	DRM_INIT_WAITQUEUE(&dev_priv->fence_queue);

	/* Turn on soft trap interrupt.  Vertical blank interrupts are enabled
	 * in mga_enable_vblank.
	 */
	MGA_WRITE(MGA_IEN, MGA_SOFTRAPEN);
	return 0;
}