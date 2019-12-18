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
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_1__* dev_private; } ;
struct TYPE_3__ {int vram_initialized; int /*<<< orphan*/  vram_offset; int /*<<< orphan*/  vram_mm; } ;
typedef  TYPE_1__ drm_sis_private_t ;
struct TYPE_4__ {int size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ drm_sis_fb_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int) ; 
 int SIS_MM_ALIGN_SHIFT ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sis_fb_init(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_sis_private_t *dev_priv = dev->dev_private;
	drm_sis_fb_t *fb = data;

	mutex_lock(&dev->struct_mutex);
	/* Unconditionally init the drm_mm, even though we don't use it when the
	 * fb sis driver is available - make cleanup easier. */
	drm_mm_init(&dev_priv->vram_mm, 0, fb->size >> SIS_MM_ALIGN_SHIFT);

	dev_priv->vram_initialized = 1;
	dev_priv->vram_offset = fb->offset;

	mutex_unlock(&dev->struct_mutex);
	DRM_DEBUG("offset = %lu, size = %lu\n", fb->offset, fb->size);

	return 0;
}