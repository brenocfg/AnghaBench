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
struct intel_ring_buffer {int /*<<< orphan*/  name; struct drm_device* dev; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int I915_READ_CTL (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  I915_WRITE_CTL (struct intel_ring_buffer*,int) ; 
 int RING_WAIT ; 

__attribute__((used)) static bool kick_ring(struct intel_ring_buffer *ring)
{
	struct drm_device *dev = ring->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 tmp = I915_READ_CTL(ring);
	if (tmp & RING_WAIT) {
		DRM_ERROR("Kicking stuck wait on %s\n",
			  ring->name);
		I915_WRITE_CTL(ring, tmp);
		return true;
	}
	return false;
}