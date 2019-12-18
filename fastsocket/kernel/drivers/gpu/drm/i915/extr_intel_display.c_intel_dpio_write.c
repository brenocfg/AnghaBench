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
struct drm_i915_private {int /*<<< orphan*/  dpio_lock; } ;

/* Variables and functions */
 int DPIO_BUSY ; 
 int DPIO_BYTE ; 
 int /*<<< orphan*/  DPIO_DATA ; 
 int DPIO_OP_WRITE ; 
 int /*<<< orphan*/  DPIO_PKT ; 
 int DPIO_PORTID ; 
 int /*<<< orphan*/  DPIO_REG ; 
 int DPIO_RID ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_atomic_us (int,int) ; 

__attribute__((used)) static void intel_dpio_write(struct drm_i915_private *dev_priv, int reg,
			     u32 val)
{
	WARN_ON(!mutex_is_locked(&dev_priv->dpio_lock));

	if (wait_for_atomic_us((I915_READ(DPIO_PKT) & DPIO_BUSY) == 0, 100)) {
		DRM_ERROR("DPIO idle wait timed out\n");
		return;
	}

	I915_WRITE(DPIO_DATA, val);
	I915_WRITE(DPIO_REG, reg);
	I915_WRITE(DPIO_PKT, DPIO_RID | DPIO_OP_WRITE | DPIO_PORTID |
		   DPIO_BYTE);
	if (wait_for_atomic_us((I915_READ(DPIO_PKT) & DPIO_BUSY) == 0, 100))
		DRM_ERROR("DPIO write wait timed out\n");
}