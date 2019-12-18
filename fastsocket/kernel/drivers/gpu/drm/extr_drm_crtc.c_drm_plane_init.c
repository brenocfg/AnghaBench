#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct drm_plane_funcs {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * properties; } ;
struct drm_plane {int format_count; unsigned long possible_crtcs; int /*<<< orphan*/  head; int /*<<< orphan*/  format_types; TYPE_2__ base; struct drm_plane_funcs const* funcs; struct drm_device* dev; int /*<<< orphan*/  properties; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_plane; int /*<<< orphan*/  plane_list; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_PLANE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int drm_mode_object_get (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_object_put (struct drm_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 

int drm_plane_init(struct drm_device *dev, struct drm_plane *plane,
		   unsigned long possible_crtcs,
		   const struct drm_plane_funcs *funcs,
		   const uint32_t *formats, uint32_t format_count,
		   bool priv)
{
	int ret;

	drm_modeset_lock_all(dev);

	ret = drm_mode_object_get(dev, &plane->base, DRM_MODE_OBJECT_PLANE);
	if (ret)
		goto out;

	plane->base.properties = &plane->properties;
	plane->dev = dev;
	plane->funcs = funcs;
	plane->format_types = kmalloc(sizeof(uint32_t) * format_count,
				      GFP_KERNEL);
	if (!plane->format_types) {
		DRM_DEBUG_KMS("out of memory when allocating plane\n");
		drm_mode_object_put(dev, &plane->base);
		ret = -ENOMEM;
		goto out;
	}

	memcpy(plane->format_types, formats, format_count * sizeof(uint32_t));
	plane->format_count = format_count;
	plane->possible_crtcs = possible_crtcs;

	/* private planes are not exposed to userspace, but depending on
	 * display hardware, might be convenient to allow sharing programming
	 * for the scanout engine with the crtc implementation.
	 */
	if (!priv) {
		list_add_tail(&plane->head, &dev->mode_config.plane_list);
		dev->mode_config.num_plane++;
	} else {
		INIT_LIST_HEAD(&plane->head);
	}

 out:
	drm_modeset_unlock_all(dev);

	return ret;
}