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
typedef  int /*<<< orphan*/  uint16_t ;
struct intel_dp {int dummy; } ;

/* Variables and functions */
 int intel_dp_aux_native_write (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
intel_dp_aux_native_write_1(struct intel_dp *intel_dp,
			    uint16_t address, uint8_t byte)
{
	return intel_dp_aux_native_write(intel_dp, address, &byte, 1);
}