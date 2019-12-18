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
struct intel_ring_buffer {int /*<<< orphan*/  private; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_BROKEN_CS_TLB (struct drm_device*) ; 
 int /*<<< orphan*/  cleanup_pipe_control (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_gem_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void render_ring_cleanup(struct intel_ring_buffer *ring)
{
	struct drm_device *dev = ring->dev;

	if (!ring->private)
		return;

	if (HAS_BROKEN_CS_TLB(dev))
		drm_gem_object_unreference(to_gem_object(ring->private));

	cleanup_pipe_control(ring);
}