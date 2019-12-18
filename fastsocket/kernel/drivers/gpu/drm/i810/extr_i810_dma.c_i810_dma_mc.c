#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct drm_file {int dummy; } ;
struct drm_device_dma {size_t buf_count; int /*<<< orphan*/ * buflist; } ;
struct drm_device {int /*<<< orphan*/ * counts; scalar_t__ dev_private; struct drm_device_dma* dma; } ;
struct TYPE_4__ {int last_dispatch; scalar_t__ last_enqueue; } ;
typedef  TYPE_1__ drm_i810_sarea_t ;
struct TYPE_5__ {scalar_t__ counter; scalar_t__ sarea_priv; scalar_t__* hw_status_page; } ;
typedef  TYPE_2__ drm_i810_private_t ;
struct TYPE_6__ {size_t idx; int /*<<< orphan*/  used; int /*<<< orphan*/  last_render; } ;
typedef  TYPE_3__ drm_i810_mc_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 size_t _DRM_STAT_DMA ; 
 size_t _DRM_STAT_SECONDARY ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i810_dma_dispatch_mc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i810_dma_mc(struct drm_device *dev, void *data,
		       struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	drm_i810_private_t *dev_priv = (drm_i810_private_t *) dev->dev_private;
	u32 *hw_status = dev_priv->hw_status_page;
	drm_i810_sarea_t *sarea_priv = (drm_i810_sarea_t *)
	    dev_priv->sarea_priv;
	drm_i810_mc_t *mc = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (mc->idx >= dma->buf_count || mc->idx < 0)
		return -EINVAL;

	i810_dma_dispatch_mc(dev, dma->buflist[mc->idx], mc->used,
			     mc->last_render);

	atomic_add(mc->used, &dev->counts[_DRM_STAT_SECONDARY]);
	atomic_inc(&dev->counts[_DRM_STAT_DMA]);
	sarea_priv->last_enqueue = dev_priv->counter - 1;
	sarea_priv->last_dispatch = (int)hw_status[5];

	return 0;
}