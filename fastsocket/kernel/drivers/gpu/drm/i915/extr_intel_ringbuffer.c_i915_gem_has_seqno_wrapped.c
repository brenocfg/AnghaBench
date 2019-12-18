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
typedef  scalar_t__ u32 ;
struct drm_i915_private {scalar_t__ last_seqno; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */

__attribute__((used)) static inline bool i915_gem_has_seqno_wrapped(struct drm_device *dev,
					      u32 seqno)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	return dev_priv->last_seqno < seqno;
}