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
typedef  int uint8_t ;
struct intel_dp {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DP_TRAIN_PRE_EMPHASIS_0 ; 
 int DP_TRAIN_PRE_EMPHASIS_3_5 ; 
 int DP_TRAIN_PRE_EMPHASIS_6 ; 
 int DP_TRAIN_PRE_EMPHASIS_9_5 ; 
#define  DP_TRAIN_VOLTAGE_SWING_1200 131 
#define  DP_TRAIN_VOLTAGE_SWING_400 130 
#define  DP_TRAIN_VOLTAGE_SWING_600 129 
#define  DP_TRAIN_VOLTAGE_SWING_800 128 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 scalar_t__ IS_GEN7 (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_device*) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 scalar_t__ is_cpu_edp (struct intel_dp*) ; 

__attribute__((used)) static uint8_t
intel_dp_pre_emphasis_max(struct intel_dp *intel_dp, uint8_t voltage_swing)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);

	if (IS_HASWELL(dev)) {
		switch (voltage_swing & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_400:
			return DP_TRAIN_PRE_EMPHASIS_9_5;
		case DP_TRAIN_VOLTAGE_SWING_600:
			return DP_TRAIN_PRE_EMPHASIS_6;
		case DP_TRAIN_VOLTAGE_SWING_800:
			return DP_TRAIN_PRE_EMPHASIS_3_5;
		case DP_TRAIN_VOLTAGE_SWING_1200:
		default:
			return DP_TRAIN_PRE_EMPHASIS_0;
		}
	} else if (IS_GEN7(dev) && is_cpu_edp(intel_dp) && !IS_VALLEYVIEW(dev)) {
		switch (voltage_swing & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_400:
			return DP_TRAIN_PRE_EMPHASIS_6;
		case DP_TRAIN_VOLTAGE_SWING_600:
		case DP_TRAIN_VOLTAGE_SWING_800:
			return DP_TRAIN_PRE_EMPHASIS_3_5;
		default:
			return DP_TRAIN_PRE_EMPHASIS_0;
		}
	} else {
		switch (voltage_swing & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_400:
			return DP_TRAIN_PRE_EMPHASIS_6;
		case DP_TRAIN_VOLTAGE_SWING_600:
			return DP_TRAIN_PRE_EMPHASIS_6;
		case DP_TRAIN_VOLTAGE_SWING_800:
			return DP_TRAIN_PRE_EMPHASIS_3_5;
		case DP_TRAIN_VOLTAGE_SWING_1200:
		default:
			return DP_TRAIN_PRE_EMPHASIS_0;
		}
	}
}