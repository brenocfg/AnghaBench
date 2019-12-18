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
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_4__ {TYPE_1__* mtrr; } ;
typedef  TYPE_2__ drm_savage_private_t ;
struct TYPE_3__ {scalar_t__ handle; int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MTRR_WC ; 
 int /*<<< orphan*/  drm_mtrr_del (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void savage_driver_lastclose(struct drm_device *dev)
{
	drm_savage_private_t *dev_priv = dev->dev_private;
	int i;

	for (i = 0; i < 3; ++i)
		if (dev_priv->mtrr[i].handle >= 0)
			drm_mtrr_del(dev_priv->mtrr[i].handle,
				 dev_priv->mtrr[i].base,
				 dev_priv->mtrr[i].size, DRM_MTRR_WC);
}