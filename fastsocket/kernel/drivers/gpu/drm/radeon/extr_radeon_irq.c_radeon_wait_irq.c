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
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  boxes; } ;
struct TYPE_4__ {int /*<<< orphan*/  swi_queue; TYPE_1__ stats; } ;
typedef  TYPE_2__ drm_radeon_private_t ;

/* Variables and functions */
 int DRM_HZ ; 
 int /*<<< orphan*/  DRM_WAIT_ON (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RADEON_BOX_WAIT_IDLE ; 
 int /*<<< orphan*/  RADEON_LAST_SWI_REG ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_wait_irq(struct drm_device * dev, int swi_nr)
{
	drm_radeon_private_t *dev_priv =
	    (drm_radeon_private_t *) dev->dev_private;
	int ret = 0;

	if (RADEON_READ(RADEON_LAST_SWI_REG) >= swi_nr)
		return 0;

	dev_priv->stats.boxes |= RADEON_BOX_WAIT_IDLE;

	DRM_WAIT_ON(ret, dev_priv->swi_queue, 3 * DRM_HZ,
		    RADEON_READ(RADEON_LAST_SWI_REG) >= swi_nr);

	return ret;
}