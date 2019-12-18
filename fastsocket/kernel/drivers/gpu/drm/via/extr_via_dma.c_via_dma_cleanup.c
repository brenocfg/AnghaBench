#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/ * virtual_start; int /*<<< orphan*/  map; } ;
struct TYPE_5__ {TYPE_1__ ring; } ;
typedef  TYPE_2__ drm_via_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  drm_core_ioremapfree (int /*<<< orphan*/ *,struct drm_device*) ; 
 int /*<<< orphan*/  via_cmdbuf_reset (TYPE_2__*) ; 

int via_dma_cleanup(struct drm_device *dev)
{
	if (dev->dev_private) {
		drm_via_private_t *dev_priv =
		    (drm_via_private_t *) dev->dev_private;

		if (dev_priv->ring.virtual_start) {
			via_cmdbuf_reset(dev_priv);

			drm_core_ioremapfree(&dev_priv->ring.map, dev);
			dev_priv->ring.virtual_start = NULL;
		}

	}

	return 0;
}