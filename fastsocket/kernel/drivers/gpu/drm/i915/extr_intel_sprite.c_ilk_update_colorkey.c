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
struct drm_intel_sprite_colorkey {int min_value; int max_value; int channel_mask; int flags; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVSCNTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVSKEYMAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVSKEYMSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVSKEYVAL (int /*<<< orphan*/ ) ; 
 int DVS_DEST_KEY ; 
 int DVS_SOURCE_KEY ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int I915_SET_COLORKEY_DESTINATION ; 
 int I915_SET_COLORKEY_SOURCE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static int
ilk_update_colorkey(struct drm_plane *plane,
		    struct drm_intel_sprite_colorkey *key)
{
	struct drm_device *dev = plane->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_plane *intel_plane;
	u32 dvscntr;
	int ret = 0;

	intel_plane = to_intel_plane(plane);

	I915_WRITE(DVSKEYVAL(intel_plane->pipe), key->min_value);
	I915_WRITE(DVSKEYMAX(intel_plane->pipe), key->max_value);
	I915_WRITE(DVSKEYMSK(intel_plane->pipe), key->channel_mask);

	dvscntr = I915_READ(DVSCNTR(intel_plane->pipe));
	dvscntr &= ~(DVS_SOURCE_KEY | DVS_DEST_KEY);
	if (key->flags & I915_SET_COLORKEY_DESTINATION)
		dvscntr |= DVS_DEST_KEY;
	else if (key->flags & I915_SET_COLORKEY_SOURCE)
		dvscntr |= DVS_SOURCE_KEY;
	I915_WRITE(DVSCNTR(intel_plane->pipe), dvscntr);

	POSTING_READ(DVSKEYMSK(intel_plane->pipe));

	return ret;
}