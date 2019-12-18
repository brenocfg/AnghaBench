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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * blit_queues; } ;
typedef  TYPE_1__ drm_via_private_t ;
typedef  int /*<<< orphan*/  drm_via_blitq_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int,int) ; 
 int DRM_HZ ; 
 int /*<<< orphan*/  DRM_WAIT_ON (int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ via_dmablit_active (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
via_dmablit_sync(struct drm_device *dev, uint32_t handle, int engine)
{

	drm_via_private_t *dev_priv = (drm_via_private_t *)dev->dev_private;
	drm_via_blitq_t *blitq = dev_priv->blit_queues + engine;
	wait_queue_head_t *queue;
	int ret = 0;

	if (via_dmablit_active(blitq, engine, handle, &queue)) {
		DRM_WAIT_ON(ret, *queue, 3 * DRM_HZ,
			    !via_dmablit_active(blitq, engine, handle, NULL));
	}
	DRM_DEBUG("DMA blit sync handle 0x%x engine %d returned %d\n",
		  handle, engine, ret);

	return ret;
}