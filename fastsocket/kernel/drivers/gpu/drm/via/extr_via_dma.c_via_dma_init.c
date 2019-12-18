#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_6__ {int /*<<< orphan*/ * virtual_start; } ;
struct TYPE_7__ {TYPE_1__ ring; } ;
typedef  TYPE_2__ drm_via_private_t ;
struct TYPE_8__ {int func; } ;
typedef  TYPE_3__ drm_via_dma_init_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CURPROC ; 
 int /*<<< orphan*/  DRM_SUSER (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
#define  VIA_CLEANUP_DMA 130 
#define  VIA_DMA_INITIALIZED 129 
#define  VIA_INIT_DMA 128 
 int via_dma_cleanup (struct drm_device*) ; 
 int via_initialize (struct drm_device*,TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int via_dma_init(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
	drm_via_dma_init_t *init = data;
	int retcode = 0;

	switch (init->func) {
	case VIA_INIT_DMA:
		if (!DRM_SUSER(DRM_CURPROC))
			retcode = -EPERM;
		else
			retcode = via_initialize(dev, dev_priv, init);
		break;
	case VIA_CLEANUP_DMA:
		if (!DRM_SUSER(DRM_CURPROC))
			retcode = -EPERM;
		else
			retcode = via_dma_cleanup(dev);
		break;
	case VIA_DMA_INITIALIZED:
		retcode = (dev_priv->ring.virtual_start != NULL) ?
			0 : -EFAULT;
		break;
	default:
		retcode = -EINVAL;
		break;
	}

	return retcode;
}