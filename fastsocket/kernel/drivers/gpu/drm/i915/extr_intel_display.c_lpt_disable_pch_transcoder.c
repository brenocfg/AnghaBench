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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int TRANS_CHICKEN2_TIMING_OVERRIDE ; 
 int TRANS_ENABLE ; 
 int TRANS_STATE_ENABLE ; 
 int /*<<< orphan*/  _TRANSACONF ; 
 int /*<<< orphan*/  _TRANSA_CHICKEN2 ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void lpt_disable_pch_transcoder(struct drm_i915_private *dev_priv)
{
	u32 val;

	val = I915_READ(_TRANSACONF);
	val &= ~TRANS_ENABLE;
	I915_WRITE(_TRANSACONF, val);
	/* wait for PCH transcoder off, transcoder state */
	if (wait_for((I915_READ(_TRANSACONF) & TRANS_STATE_ENABLE) == 0, 50))
		DRM_ERROR("Failed to disable PCH transcoder\n");

	/* Workaround: clear timing override bit. */
	val = I915_READ(_TRANSA_CHICKEN2);
	val &= ~TRANS_CHICKEN2_TIMING_OVERRIDE;
	I915_WRITE(_TRANSA_CHICKEN2, val);
}