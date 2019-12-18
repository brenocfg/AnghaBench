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
typedef  int /*<<< orphan*/  uint8_t ;
struct intel_dp {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TRAIN_VOLTAGE_SWING_1200 ; 
 int /*<<< orphan*/  DP_TRAIN_VOLTAGE_SWING_800 ; 
 scalar_t__ HAS_PCH_CPT (struct drm_device*) ; 
 scalar_t__ IS_GEN7 (struct drm_device*) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 scalar_t__ is_cpu_edp (struct intel_dp*) ; 

__attribute__((used)) static uint8_t
intel_dp_voltage_max(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);

	if (IS_GEN7(dev) && is_cpu_edp(intel_dp))
		return DP_TRAIN_VOLTAGE_SWING_800;
	else if (HAS_PCH_CPT(dev) && !is_cpu_edp(intel_dp))
		return DP_TRAIN_VOLTAGE_SWING_1200;
	else
		return DP_TRAIN_VOLTAGE_SWING_800;
}