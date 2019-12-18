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
struct drm_encoder {int /*<<< orphan*/  head; int /*<<< orphan*/  base; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_encoder; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_object_put (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void drm_encoder_cleanup(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	drm_modeset_lock_all(dev);
	drm_mode_object_put(dev, &encoder->base);
	list_del(&encoder->head);
	dev->mode_config.num_encoder--;
	drm_modeset_unlock_all(dev);
}