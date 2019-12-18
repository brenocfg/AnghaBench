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
struct drm_device_dma {int buf_count; struct drm_buf** buflist; } ;
struct drm_device {TYPE_1__* dev_private; struct drm_device_dma* dma; } ;
struct drm_buf {TYPE_2__* dev_private; } ;
struct TYPE_3__ {scalar_t__ last_buf; } ;
typedef  TYPE_1__ drm_radeon_private_t ;
struct TYPE_4__ {scalar_t__ age; } ;
typedef  TYPE_2__ drm_radeon_buf_priv_t ;

/* Variables and functions */

void radeon_freelist_reset(struct drm_device * dev)
{
	struct drm_device_dma *dma = dev->dma;
	drm_radeon_private_t *dev_priv = dev->dev_private;
	int i;

	dev_priv->last_buf = 0;
	for (i = 0; i < dma->buf_count; i++) {
		struct drm_buf *buf = dma->buflist[i];
		drm_radeon_buf_priv_t *buf_priv = buf->dev_private;
		buf_priv->age = 0;
	}
}