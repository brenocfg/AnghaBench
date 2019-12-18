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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  ECOBUS ; 
 int /*<<< orphan*/  FORCEWAKE_ACK_HSW ; 
 int /*<<< orphan*/  FORCEWAKE_ACK_TIMEOUT_MS ; 
 int /*<<< orphan*/  FORCEWAKE_KERNEL ; 
 int /*<<< orphan*/  FORCEWAKE_MT ; 
 int /*<<< orphan*/  FORCEWAKE_MT_ACK ; 
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_NOTRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HASWELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __gen6_gt_wait_for_thread_c0 (struct drm_i915_private*) ; 
 scalar_t__ wait_for_atomic (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __gen6_gt_force_wake_mt_get(struct drm_i915_private *dev_priv)
{
	u32 forcewake_ack;

	if (IS_HASWELL(dev_priv->dev))
		forcewake_ack = FORCEWAKE_ACK_HSW;
	else
		forcewake_ack = FORCEWAKE_MT_ACK;

	if (wait_for_atomic((I915_READ_NOTRACE(forcewake_ack) & 1) == 0,
			    FORCEWAKE_ACK_TIMEOUT_MS))
		DRM_ERROR("Timed out waiting for forcewake old ack to clear.\n");

	I915_WRITE_NOTRACE(FORCEWAKE_MT, _MASKED_BIT_ENABLE(FORCEWAKE_KERNEL));
	/* something from same cacheline, but !FORCEWAKE_MT */
	POSTING_READ(ECOBUS);

	if (wait_for_atomic((I915_READ_NOTRACE(forcewake_ack) & 1),
			    FORCEWAKE_ACK_TIMEOUT_MS))
		DRM_ERROR("Timed out waiting for forcewake to ack request.\n");

	__gen6_gt_wait_for_thread_c0(dev_priv);
}