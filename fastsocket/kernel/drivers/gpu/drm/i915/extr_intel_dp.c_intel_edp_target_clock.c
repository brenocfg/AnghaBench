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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {struct intel_connector* attached_connector; } ;
struct TYPE_4__ {TYPE_1__* fixed_mode; } ;
struct intel_connector {TYPE_2__ panel; } ;
struct drm_display_mode {int clock; } ;
struct TYPE_3__ {int clock; } ;

/* Variables and functions */
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 

int
intel_edp_target_clock(struct intel_encoder *intel_encoder,
		       struct drm_display_mode *mode)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&intel_encoder->base);
	struct intel_connector *intel_connector = intel_dp->attached_connector;

	if (intel_connector->panel.fixed_mode)
		return intel_connector->panel.fixed_mode->clock;
	else
		return mode->clock;
}