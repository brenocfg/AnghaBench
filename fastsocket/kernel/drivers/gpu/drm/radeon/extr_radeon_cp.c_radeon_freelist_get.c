#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct drm_device_dma {int buf_count; struct drm_buf** buflist; } ;
struct drm_device {TYPE_2__* dev_private; struct drm_device_dma* dma; } ;
struct drm_buf {scalar_t__ pending; int /*<<< orphan*/ * file_priv; TYPE_3__* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  freelist_loops; int /*<<< orphan*/  requested_bufs; } ;
struct TYPE_6__ {int last_buf; int usec_timeout; TYPE_1__ stats; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_7__ {scalar_t__ age; } ;
typedef  TYPE_3__ drm_radeon_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 scalar_t__ GET_SCRATCH (TYPE_2__*,int) ; 

struct drm_buf *radeon_freelist_get(struct drm_device * dev)
{
	struct drm_device_dma *dma = dev->dma;
	drm_radeon_private_t *dev_priv = dev->dev_private;
	drm_radeon_buf_priv_t *buf_priv;
	struct drm_buf *buf;
	int i, t;
	int start;

	if (++dev_priv->last_buf >= dma->buf_count)
		dev_priv->last_buf = 0;

	start = dev_priv->last_buf;

	for (t = 0; t < dev_priv->usec_timeout; t++) {
		u32 done_age = GET_SCRATCH(dev_priv, 1);
		DRM_DEBUG("done_age = %d\n", done_age);
		for (i = 0; i < dma->buf_count; i++) {
			buf = dma->buflist[start];
			buf_priv = buf->dev_private;
			if (buf->file_priv == NULL || (buf->pending &&
						       buf_priv->age <=
						       done_age)) {
				dev_priv->stats.requested_bufs++;
				buf->pending = 0;
				return buf;
			}
			if (++start >= dma->buf_count)
				start = 0;
		}

		if (t) {
			DRM_UDELAY(1);
			dev_priv->stats.freelist_loops++;
		}
	}

	return NULL;
}