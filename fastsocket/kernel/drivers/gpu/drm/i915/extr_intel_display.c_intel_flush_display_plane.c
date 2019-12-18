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
struct drm_i915_private {TYPE_1__* info; } ;
typedef  enum plane { ____Placeholder_plane } plane ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSPADDR (int) ; 
 int /*<<< orphan*/  DSPSURF (int) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_flush_display_plane(struct drm_i915_private *dev_priv,
				      enum plane plane)
{
	if (dev_priv->info->gen >= 4)
		I915_WRITE(DSPSURF(plane), I915_READ(DSPSURF(plane)));
	else
		I915_WRITE(DSPADDR(plane), I915_READ(DSPADDR(plane)));
}