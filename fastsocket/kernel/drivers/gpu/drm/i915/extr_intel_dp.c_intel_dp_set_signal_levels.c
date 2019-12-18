#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct intel_dp {int /*<<< orphan*/ * train_set; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_3__ {TYPE_2__ base; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DDI_BUF_EMP_MASK ; 
 int DP_PRE_EMPHASIS_MASK ; 
 int DP_VOLTAGE_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int EDP_LINK_TRAIN_VOL_EMP_MASK_IVB ; 
 int EDP_LINK_TRAIN_VOL_EMP_MASK_SNB ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 scalar_t__ IS_GEN7 (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_device*) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int intel_gen4_signal_levels (int /*<<< orphan*/ ) ; 
 int intel_gen6_edp_signal_levels (int /*<<< orphan*/ ) ; 
 int intel_gen7_edp_signal_levels (int /*<<< orphan*/ ) ; 
 int intel_hsw_signal_levels (int /*<<< orphan*/ ) ; 
 scalar_t__ is_cpu_edp (struct intel_dp*) ; 

__attribute__((used)) static void
intel_dp_set_signal_levels(struct intel_dp *intel_dp, uint32_t *DP)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;
	uint32_t signal_levels, mask;
	uint8_t train_set = intel_dp->train_set[0];

	if (IS_HASWELL(dev)) {
		signal_levels = intel_hsw_signal_levels(train_set);
		mask = DDI_BUF_EMP_MASK;
	} else if (IS_GEN7(dev) && is_cpu_edp(intel_dp) && !IS_VALLEYVIEW(dev)) {
		signal_levels = intel_gen7_edp_signal_levels(train_set);
		mask = EDP_LINK_TRAIN_VOL_EMP_MASK_IVB;
	} else if (IS_GEN6(dev) && is_cpu_edp(intel_dp)) {
		signal_levels = intel_gen6_edp_signal_levels(train_set);
		mask = EDP_LINK_TRAIN_VOL_EMP_MASK_SNB;
	} else {
		signal_levels = intel_gen4_signal_levels(train_set);
		mask = DP_VOLTAGE_MASK | DP_PRE_EMPHASIS_MASK;
	}

	DRM_DEBUG_KMS("Using signal levels %08x\n", signal_levels);

	*DP = (*DP & ~mask) | signal_levels;
}