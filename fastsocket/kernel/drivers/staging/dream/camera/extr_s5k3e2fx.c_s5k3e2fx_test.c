#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ int32_t ;
typedef  enum msm_s_test_mode { ____Placeholder_msm_s_test_mode } msm_s_test_mode ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TEST_PATTERN_MODE ; 
 int S_TEST_OFF ; 
 TYPE_1__* s5k3e2fx_client ; 
 scalar_t__ s5k3e2fx_i2c_write_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t s5k3e2fx_test(enum msm_s_test_mode mo)
{
	int32_t rc = 0;

	if (mo == S_TEST_OFF)
		rc = 0;
	else
		rc = s5k3e2fx_i2c_write_b(s5k3e2fx_client->addr,
			REG_TEST_PATTERN_MODE, (uint16_t)mo);

	return rc;
}