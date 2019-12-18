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
struct drm_file {int dummy; } ;
struct drm_device_dma {int buf_count; TYPE_1__** buflist; } ;
struct drm_device {struct drm_device_dma* dma; } ;
struct TYPE_2__ {int list; struct drm_file* file_priv; } ;

/* Variables and functions */
#define  DRM_LIST_NONE 129 
 int DRM_LIST_RECLAIM ; 
#define  DRM_LIST_WAIT 128 
 int /*<<< orphan*/  drm_free_buffer (struct drm_device*,TYPE_1__*) ; 

void drm_core_reclaim_buffers(struct drm_device *dev,
			      struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	int i;

	if (!dma)
		return;
	for (i = 0; i < dma->buf_count; i++) {
		if (dma->buflist[i]->file_priv == file_priv) {
			switch (dma->buflist[i]->list) {
			case DRM_LIST_NONE:
				drm_free_buffer(dev, dma->buflist[i]);
				break;
			case DRM_LIST_WAIT:
				dma->buflist[i]->list = DRM_LIST_RECLAIM;
				break;
			default:
				/* Buffer already on hardware. */
				break;
			}
		}
	}
}