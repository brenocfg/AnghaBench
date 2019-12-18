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
typedef  int /*<<< orphan*/  u8 ;
struct intel_dp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEVICE_SERVICE_IRQ_VECTOR ; 
 int intel_dp_aux_native_read_retry (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
intel_dp_get_sink_irq(struct intel_dp *intel_dp, u8 *sink_irq_vector)
{
	int ret;

	ret = intel_dp_aux_native_read_retry(intel_dp,
					     DP_DEVICE_SERVICE_IRQ_VECTOR,
					     sink_irq_vector, 1);
	if (!ret)
		return false;

	return true;
}