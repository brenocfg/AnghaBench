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
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_1__* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mmio; scalar_t__ agp_initialized; int /*<<< orphan*/  agp_mm; scalar_t__ vram_initialized; int /*<<< orphan*/  vram_mm; } ;
typedef  TYPE_1__ drm_sis_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void sis_lastclose(struct drm_device *dev)
{
	drm_sis_private_t *dev_priv = dev->dev_private;

	if (!dev_priv)
		return;

	mutex_lock(&dev->struct_mutex);
	if (dev_priv->vram_initialized) {
		drm_mm_takedown(&dev_priv->vram_mm);
		dev_priv->vram_initialized = 0;
	}
	if (dev_priv->agp_initialized) {
		drm_mm_takedown(&dev_priv->agp_mm);
		dev_priv->agp_initialized = 0;
	}
	dev_priv->mmio = NULL;
	mutex_unlock(&dev->struct_mutex);
}