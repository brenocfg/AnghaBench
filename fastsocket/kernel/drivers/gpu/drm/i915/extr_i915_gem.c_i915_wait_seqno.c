#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct intel_ring_buffer {struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  reset_counter; } ;
struct TYPE_3__ {int interruptible; } ;
struct drm_i915_private {TYPE_2__ gpu_error; TYPE_1__ mm; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __wait_seqno (struct intel_ring_buffer*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int i915_gem_check_olr (struct intel_ring_buffer*,scalar_t__) ; 
 int i915_gem_check_wedge (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

int
i915_wait_seqno(struct intel_ring_buffer *ring, uint32_t seqno)
{
	struct drm_device *dev = ring->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	bool interruptible = dev_priv->mm.interruptible;
	int ret;

	BUG_ON(!mutex_is_locked(&dev->struct_mutex));
	BUG_ON(seqno == 0);

	ret = i915_gem_check_wedge(&dev_priv->gpu_error, interruptible);
	if (ret)
		return ret;

	ret = i915_gem_check_olr(ring, seqno);
	if (ret)
		return ret;

	return __wait_seqno(ring, seqno,
			    atomic_read(&dev_priv->gpu_error.reset_counter),
			    interruptible, NULL);
}