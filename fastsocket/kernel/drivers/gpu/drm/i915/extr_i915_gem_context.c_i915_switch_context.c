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
struct intel_ring_buffer {struct i915_hw_context* default_context; TYPE_1__* dev; } ;
struct i915_hw_context {int dummy; } ;
struct drm_i915_private {struct intel_ring_buffer* ring; scalar_t__ hw_contexts_disabled; } ;
struct drm_file {int /*<<< orphan*/  driver_priv; } ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int DEFAULT_CONTEXT_ID ; 
 int EINVAL ; 
 int ENOENT ; 
 size_t RCS ; 
 int do_switch (struct i915_hw_context*) ; 
 struct i915_hw_context* i915_gem_context_get (int /*<<< orphan*/ ,int) ; 

int i915_switch_context(struct intel_ring_buffer *ring,
			struct drm_file *file,
			int to_id)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;
	struct i915_hw_context *to;

	if (dev_priv->hw_contexts_disabled)
		return 0;

	if (ring != &dev_priv->ring[RCS])
		return 0;

	if (to_id == DEFAULT_CONTEXT_ID) {
		to = ring->default_context;
	} else {
		if (file == NULL)
			return -EINVAL;

		to = i915_gem_context_get(file->driver_priv, to_id);
		if (to == NULL)
			return -ENOENT;
	}

	return do_switch(to);
}