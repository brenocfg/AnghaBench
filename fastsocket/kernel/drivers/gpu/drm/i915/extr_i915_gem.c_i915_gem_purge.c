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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 long __i915_gem_shrink (struct drm_i915_private*,long,int) ; 

__attribute__((used)) static long
i915_gem_purge(struct drm_i915_private *dev_priv, long target)
{
	return __i915_gem_shrink(dev_priv, target, true);
}