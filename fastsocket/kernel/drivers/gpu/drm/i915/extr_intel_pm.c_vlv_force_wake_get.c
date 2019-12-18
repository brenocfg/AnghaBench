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
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  FORCEWAKE_ACK_TIMEOUT_MS ; 
 int /*<<< orphan*/  FORCEWAKE_ACK_VLV ; 
 int /*<<< orphan*/  FORCEWAKE_KERNEL ; 
 int /*<<< orphan*/  FORCEWAKE_VLV ; 
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_NOTRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __gen6_gt_wait_for_thread_c0 (struct drm_i915_private*) ; 
 scalar_t__ wait_for_atomic (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlv_force_wake_get(struct drm_i915_private *dev_priv)
{
	if (wait_for_atomic((I915_READ_NOTRACE(FORCEWAKE_ACK_VLV) & 1) == 0,
			    FORCEWAKE_ACK_TIMEOUT_MS))
		DRM_ERROR("Timed out waiting for forcewake old ack to clear.\n");

	I915_WRITE_NOTRACE(FORCEWAKE_VLV, _MASKED_BIT_ENABLE(FORCEWAKE_KERNEL));

	if (wait_for_atomic((I915_READ_NOTRACE(FORCEWAKE_ACK_VLV) & 1),
			    FORCEWAKE_ACK_TIMEOUT_MS))
		DRM_ERROR("Timed out waiting for forcewake to ack request.\n");

	__gen6_gt_wait_for_thread_c0(dev_priv);
}