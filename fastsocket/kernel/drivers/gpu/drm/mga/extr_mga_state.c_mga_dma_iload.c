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
struct drm_file {int dummy; } ;
struct drm_device_dma {size_t buf_count; struct drm_buf** buflist; } ;
struct drm_device {TYPE_2__* dev_private; struct drm_device_dma* dma; } ;
struct drm_buf {int /*<<< orphan*/ * dev_private; } ;
struct TYPE_8__ {TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
struct TYPE_9__ {size_t idx; int /*<<< orphan*/  length; int /*<<< orphan*/  dstorg; } ;
typedef  TYPE_3__ drm_mga_iload_t ;
typedef  int /*<<< orphan*/  drm_mga_buf_priv_t ;
struct TYPE_7__ {int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 scalar_t__ MGA_DMA_DEBUG ; 
 int /*<<< orphan*/  MGA_UPLOAD_CONTEXT ; 
 int /*<<< orphan*/  WRAP_TEST_WITH_RETURN (TYPE_2__*) ; 
 int /*<<< orphan*/  mga_dma_dispatch_iload (struct drm_device*,struct drm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mga_do_wait_for_idle (TYPE_2__*) ; 
 int /*<<< orphan*/  mga_freelist_put (struct drm_device*,struct drm_buf*) ; 
 scalar_t__ mga_verify_iload (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mga_dma_iload(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	drm_mga_private_t *dev_priv = dev->dev_private;
	struct drm_buf *buf;
	drm_mga_buf_priv_t *buf_priv;
	drm_mga_iload_t *iload = data;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

#if 0
	if (mga_do_wait_for_idle(dev_priv) < 0) {
		if (MGA_DMA_DEBUG)
			DRM_INFO("-EBUSY\n");
		return -EBUSY;
	}
#endif
	if (iload->idx < 0 || iload->idx > dma->buf_count)
		return -EINVAL;

	buf = dma->buflist[iload->idx];
	buf_priv = buf->dev_private;

	if (mga_verify_iload(dev_priv, iload->dstorg, iload->length)) {
		mga_freelist_put(dev, buf);
		return -EINVAL;
	}

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_iload(dev, buf, iload->dstorg, iload->length);

	/* Make sure we restore the 3D state next time.
	 */
	dev_priv->sarea_priv->dirty |= MGA_UPLOAD_CONTEXT;

	return 0;
}