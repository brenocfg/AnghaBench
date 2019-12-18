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
struct intel_plane {int pipe; scalar_t__ can_scale; } ;
struct drm_plane {struct drm_device* dev; } ;
struct drm_i915_private {int sprite_scaling_enabled; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_MODIFY_DISPBASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRCTL (int) ; 
 int SPRITE_ENABLE ; 
 int /*<<< orphan*/  SPRSCALE (int) ; 
 int /*<<< orphan*/  SPRSURF (int) ; 
 int /*<<< orphan*/  intel_update_watermarks (struct drm_device*) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static void
ivb_disable_plane(struct drm_plane *plane)
{
	struct drm_device *dev = plane->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_plane *intel_plane = to_intel_plane(plane);
	int pipe = intel_plane->pipe;
	bool scaling_was_enabled = dev_priv->sprite_scaling_enabled;

	I915_WRITE(SPRCTL(pipe), I915_READ(SPRCTL(pipe)) & ~SPRITE_ENABLE);
	/* Can't leave the scaler enabled... */
	if (intel_plane->can_scale)
		I915_WRITE(SPRSCALE(pipe), 0);
	/* Activate double buffered register update */
	I915_MODIFY_DISPBASE(SPRSURF(pipe), 0);
	POSTING_READ(SPRSURF(pipe));

	dev_priv->sprite_scaling_enabled &= ~(1 << pipe);

	/* potentially re-enable LP watermarks */
	if (scaling_was_enabled && !dev_priv->sprite_scaling_enabled)
		intel_update_watermarks(dev);
}