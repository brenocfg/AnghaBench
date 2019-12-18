#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_ring_buffer {int space; int /*<<< orphan*/  head; struct drm_device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  interruptible; } ;
struct drm_i915_private {TYPE_4__ mm; int /*<<< orphan*/  gpu_error; } ;
struct drm_i915_master_private {TYPE_3__* sarea_priv; } ;
struct drm_device {TYPE_2__* primary; struct drm_i915_private* dev_private; } ;
struct TYPE_7__ {int /*<<< orphan*/  perf_boxes; } ;
struct TYPE_6__ {TYPE_1__* master; } ;
struct TYPE_5__ {struct drm_i915_master_private* driver_priv; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOSPC ; 
 int HZ ; 
 int /*<<< orphan*/  I915_BOX_WAIT ; 
 int /*<<< orphan*/  I915_READ_HEAD (struct intel_ring_buffer*) ; 
 int i915_gem_check_wedge (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int intel_ring_wait_request (struct intel_ring_buffer*,int) ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ring_space (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  time_after (int,unsigned long) ; 
 int /*<<< orphan*/  trace_i915_ring_wait_begin (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  trace_i915_ring_wait_end (struct intel_ring_buffer*) ; 

__attribute__((used)) static int ring_wait_for_space(struct intel_ring_buffer *ring, int n)
{
	struct drm_device *dev = ring->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long end;
	int ret;

	ret = intel_ring_wait_request(ring, n);
	if (ret != -ENOSPC)
		return ret;

	trace_i915_ring_wait_begin(ring);
	/* With GEM the hangcheck timer should kick us out of the loop,
	 * leaving it early runs the risk of corrupting GEM state (due
	 * to running on almost untested codepaths). But on resume
	 * timers don't work yet, so prevent a complete hang in that
	 * case by choosing an insanely large timeout. */
	end = jiffies + 60 * HZ;

	do {
		ring->head = I915_READ_HEAD(ring);
		ring->space = ring_space(ring);
		if (ring->space >= n) {
			trace_i915_ring_wait_end(ring);
			return 0;
		}

		if (dev->primary->master) {
			struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;
			if (master_priv->sarea_priv)
				master_priv->sarea_priv->perf_boxes |= I915_BOX_WAIT;
		}

		msleep(1);

		ret = i915_gem_check_wedge(&dev_priv->gpu_error,
					   dev_priv->mm.interruptible);
		if (ret)
			return ret;
	} while (!time_after(jiffies, end));
	trace_i915_ring_wait_end(ring);
	return -EBUSY;
}