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
struct TYPE_7__ {int /*<<< orphan*/  boxes; } ;
struct TYPE_8__ {int usec_timeout; TYPE_1__ stats; } ;
typedef  TYPE_2__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  R300_VAP_CNTL_STATUS ; 
 int /*<<< orphan*/  RADEON_BOX_WAIT_IDLE ; 
 int RADEON_RBBM_ACTIVE ; 
 int /*<<< orphan*/  RADEON_RBBM_STATUS ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_do_pixcache_flush (TYPE_2__*) ; 
 int radeon_do_wait_for_fifo (TYPE_2__*,int) ; 
 int /*<<< orphan*/  radeon_status (TYPE_2__*) ; 

__attribute__((used)) static int radeon_do_wait_for_idle(drm_radeon_private_t * dev_priv)
{
	int i, ret;

	dev_priv->stats.boxes |= RADEON_BOX_WAIT_IDLE;

	ret = radeon_do_wait_for_fifo(dev_priv, 64);
	if (ret)
		return ret;

	for (i = 0; i < dev_priv->usec_timeout; i++) {
		if (!(RADEON_READ(RADEON_RBBM_STATUS)
		      & RADEON_RBBM_ACTIVE)) {
			radeon_do_pixcache_flush(dev_priv);
			return 0;
		}
		DRM_UDELAY(1);
	}
	DRM_DEBUG("wait idle failed status : 0x%08X 0x%08X\n",
		 RADEON_READ(RADEON_RBBM_STATUS),
		 RADEON_READ(R300_VAP_CNTL_STATUS));

#if RADEON_FIFO_DEBUG
	DRM_ERROR("failed!\n");
	radeon_status(dev_priv);
#endif
	return -EBUSY;
}