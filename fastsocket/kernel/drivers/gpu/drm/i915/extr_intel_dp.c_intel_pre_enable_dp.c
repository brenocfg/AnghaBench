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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int dummy; } ;

/* Variables and functions */
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ironlake_edp_pll_on (struct intel_dp*) ; 
 scalar_t__ is_cpu_edp (struct intel_dp*) ; 

__attribute__((used)) static void intel_pre_enable_dp(struct intel_encoder *encoder)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);

	if (is_cpu_edp(intel_dp))
		ironlake_edp_pll_on(intel_dp);
}