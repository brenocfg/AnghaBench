#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int usec_timeout; } ;
typedef  TYPE_1__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int EBUSY ; 
 int R128_GUI_ACTIVE ; 
 int /*<<< orphan*/  R128_GUI_STAT ; 
 int R128_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r128_do_pixcache_flush (TYPE_1__*) ; 
 int r128_do_wait_for_fifo (TYPE_1__*,int) ; 

__attribute__((used)) static int r128_do_wait_for_idle(drm_r128_private_t *dev_priv)
{
	int i, ret;

	ret = r128_do_wait_for_fifo(dev_priv, 64);
	if (ret)
		return ret;

	for (i = 0; i < dev_priv->usec_timeout; i++) {
		if (!(R128_READ(R128_GUI_STAT) & R128_GUI_ACTIVE)) {
			r128_do_pixcache_flush(dev_priv);
			return 0;
		}
		DRM_UDELAY(1);
	}

#if R128_FIFO_DEBUG
	DRM_ERROR("failed!\n");
#endif
	return -EBUSY;
}