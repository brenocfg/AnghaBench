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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  hw_lock; } ;
struct drm_i915_private {TYPE_1__ rps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GEN6_PCODE_DATA ; 
 int /*<<< orphan*/  GEN6_PCODE_MAILBOX ; 
 int GEN6_PCODE_READY ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for (int,int) ; 

int sandybridge_pcode_read(struct drm_i915_private *dev_priv, u8 mbox, u32 *val)
{
	WARN_ON(!mutex_is_locked(&dev_priv->rps.hw_lock));

	if (I915_READ(GEN6_PCODE_MAILBOX) & GEN6_PCODE_READY) {
		DRM_DEBUG_DRIVER("warning: pcode (read) mailbox access failed\n");
		return -EAGAIN;
	}

	I915_WRITE(GEN6_PCODE_DATA, *val);
	I915_WRITE(GEN6_PCODE_MAILBOX, GEN6_PCODE_READY | mbox);

	if (wait_for((I915_READ(GEN6_PCODE_MAILBOX) & GEN6_PCODE_READY) == 0,
		     500)) {
		DRM_ERROR("timeout waiting for pcode read (%d) to finish\n", mbox);
		return -ETIMEDOUT;
	}

	*val = I915_READ(GEN6_PCODE_DATA);
	I915_WRITE(GEN6_PCODE_DATA, 0);

	return 0;
}