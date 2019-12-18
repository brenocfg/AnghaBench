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
struct drm_plane {int /*<<< orphan*/  head; int /*<<< orphan*/  base; int /*<<< orphan*/  format_types; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_plane; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_object_put (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void drm_plane_cleanup(struct drm_plane *plane)
{
	struct drm_device *dev = plane->dev;

	drm_modeset_lock_all(dev);
	kfree(plane->format_types);
	drm_mode_object_put(dev, &plane->base);
	/* if not added to a list, it must be a private plane */
	if (!list_empty(&plane->head)) {
		list_del(&plane->head);
		dev->mode_config.num_plane--;
	}
	drm_modeset_unlock_all(dev);
}