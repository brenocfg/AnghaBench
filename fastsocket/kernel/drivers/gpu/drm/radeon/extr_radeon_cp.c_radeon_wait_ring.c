#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int space; int tail; scalar_t__ size; } ;
typedef  TYPE_2__ drm_radeon_ring_buffer_t ;
struct TYPE_7__ {int /*<<< orphan*/  boxes; } ;
struct TYPE_9__ {int usec_timeout; TYPE_1__ stats; TYPE_2__ ring; } ;
typedef  TYPE_3__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int EBUSY ; 
 int GET_RING_HEAD (TYPE_3__*) ; 
 int /*<<< orphan*/  RADEON_BOX_WAIT_IDLE ; 
 int /*<<< orphan*/  radeon_status (TYPE_3__*) ; 

int radeon_wait_ring(drm_radeon_private_t * dev_priv, int n)
{
	drm_radeon_ring_buffer_t *ring = &dev_priv->ring;
	int i;
	u32 last_head = GET_RING_HEAD(dev_priv);

	for (i = 0; i < dev_priv->usec_timeout; i++) {
		u32 head = GET_RING_HEAD(dev_priv);

		ring->space = (head - ring->tail) * sizeof(u32);
		if (ring->space <= 0)
			ring->space += ring->size;
		if (ring->space > n)
			return 0;

		dev_priv->stats.boxes |= RADEON_BOX_WAIT_IDLE;

		if (head != last_head)
			i = 0;
		last_head = head;

		DRM_UDELAY(1);
	}

	/* FIXME: This return value is ignored in the BEGIN_RING macro! */
#if RADEON_FIFO_DEBUG
	radeon_status(dev_priv);
	DRM_ERROR("failed!\n");
#endif
	return -EBUSY;
}