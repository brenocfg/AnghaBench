#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tail; } ;
struct TYPE_8__ {int usec_timeout; int cce_fifo_size; TYPE_1__ ring; } ;
typedef  TYPE_2__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int EBUSY ; 
 scalar_t__ GET_RING_HEAD (TYPE_2__*) ; 
 int R128_PM4_BUSY ; 
 int R128_PM4_FIFOCNT_MASK ; 
 int R128_PM4_GUI_ACTIVE ; 
 int /*<<< orphan*/  R128_PM4_STAT ; 
 int R128_READ (int /*<<< orphan*/ ) ; 
 int r128_do_pixcache_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  r128_status (TYPE_2__*) ; 

int r128_do_cce_idle(drm_r128_private_t *dev_priv)
{
	int i;

	for (i = 0; i < dev_priv->usec_timeout; i++) {
		if (GET_RING_HEAD(dev_priv) == dev_priv->ring.tail) {
			int pm4stat = R128_READ(R128_PM4_STAT);
			if (((pm4stat & R128_PM4_FIFOCNT_MASK) >=
			     dev_priv->cce_fifo_size) &&
			    !(pm4stat & (R128_PM4_BUSY |
					 R128_PM4_GUI_ACTIVE))) {
				return r128_do_pixcache_flush(dev_priv);
			}
		}
		DRM_UDELAY(1);
	}

#if R128_FIFO_DEBUG
	DRM_ERROR("failed!\n");
	r128_status(dev_priv);
#endif
	return -EBUSY;
}