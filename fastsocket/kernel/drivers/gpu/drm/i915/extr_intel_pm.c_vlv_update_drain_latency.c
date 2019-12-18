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
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int DDL_CURSORA_PRECISION_16 ; 
 int DDL_CURSORA_PRECISION_32 ; 
 int DDL_CURSORA_SHIFT ; 
 int DDL_CURSORB_PRECISION_16 ; 
 int DDL_CURSORB_PRECISION_32 ; 
 int DDL_CURSORB_SHIFT ; 
 int DDL_PLANEA_PRECISION_16 ; 
 int DDL_PLANEA_PRECISION_32 ; 
 int DDL_PLANEB_PRECISION_16 ; 
 int DDL_PLANEB_PRECISION_32 ; 
 int DRAIN_LATENCY_PRECISION_32 ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VLV_DDL1 ; 
 int /*<<< orphan*/  VLV_DDL2 ; 
 scalar_t__ vlv_compute_drain_latency (struct drm_device*,int,int*,int*,int*,int*) ; 

__attribute__((used)) static void vlv_update_drain_latency(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int planea_prec, planea_dl, planeb_prec, planeb_dl;
	int cursora_prec, cursora_dl, cursorb_prec, cursorb_dl;
	int plane_prec_mult, cursor_prec_mult; /* Precision multiplier is
							either 16 or 32 */

	/* For plane A, Cursor A */
	if (vlv_compute_drain_latency(dev, 0, &plane_prec_mult, &planea_dl,
				      &cursor_prec_mult, &cursora_dl)) {
		cursora_prec = (cursor_prec_mult == DRAIN_LATENCY_PRECISION_32) ?
			DDL_CURSORA_PRECISION_32 : DDL_CURSORA_PRECISION_16;
		planea_prec = (plane_prec_mult == DRAIN_LATENCY_PRECISION_32) ?
			DDL_PLANEA_PRECISION_32 : DDL_PLANEA_PRECISION_16;

		I915_WRITE(VLV_DDL1, cursora_prec |
				(cursora_dl << DDL_CURSORA_SHIFT) |
				planea_prec | planea_dl);
	}

	/* For plane B, Cursor B */
	if (vlv_compute_drain_latency(dev, 1, &plane_prec_mult, &planeb_dl,
				      &cursor_prec_mult, &cursorb_dl)) {
		cursorb_prec = (cursor_prec_mult == DRAIN_LATENCY_PRECISION_32) ?
			DDL_CURSORB_PRECISION_32 : DDL_CURSORB_PRECISION_16;
		planeb_prec = (plane_prec_mult == DRAIN_LATENCY_PRECISION_32) ?
			DDL_PLANEB_PRECISION_32 : DDL_PLANEB_PRECISION_16;

		I915_WRITE(VLV_DDL2, cursorb_prec |
				(cursorb_dl << DDL_CURSORB_SHIFT) |
				planeb_prec | planeb_dl);
	}
}