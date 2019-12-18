#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct intel_plane {int /*<<< orphan*/  pipe; } ;
struct drm_plane {struct drm_device* dev; } ;
struct drm_intel_sprite_colorkey {scalar_t__ flags; void* channel_mask; void* max_value; void* min_value; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 void* I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ I915_SET_COLORKEY_DESTINATION ; 
 scalar_t__ I915_SET_COLORKEY_NONE ; 
 scalar_t__ I915_SET_COLORKEY_SOURCE ; 
 int /*<<< orphan*/  SPRCTL (int /*<<< orphan*/ ) ; 
 int SPRITE_DEST_KEY ; 
 int SPRITE_SOURCE_KEY ; 
 int /*<<< orphan*/  SPRKEYMAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRKEYMSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRKEYVAL (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static void
ivb_get_colorkey(struct drm_plane *plane, struct drm_intel_sprite_colorkey *key)
{
	struct drm_device *dev = plane->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_plane *intel_plane;
	u32 sprctl;

	intel_plane = to_intel_plane(plane);

	key->min_value = I915_READ(SPRKEYVAL(intel_plane->pipe));
	key->max_value = I915_READ(SPRKEYMAX(intel_plane->pipe));
	key->channel_mask = I915_READ(SPRKEYMSK(intel_plane->pipe));
	key->flags = 0;

	sprctl = I915_READ(SPRCTL(intel_plane->pipe));

	if (sprctl & SPRITE_DEST_KEY)
		key->flags = I915_SET_COLORKEY_DESTINATION;
	else if (sprctl & SPRITE_SOURCE_KEY)
		key->flags = I915_SET_COLORKEY_SOURCE;
	else
		key->flags = I915_SET_COLORKEY_NONE;
}