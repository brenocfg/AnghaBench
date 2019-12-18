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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ int32_t ;
typedef  enum mt9p012_test_mode { ____Placeholder_mt9p012_test_mode } mt9p012_test_mode ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ttbl_size; int /*<<< orphan*/  ttbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPED_PARAMETER_HOLD ; 
 int /*<<< orphan*/  GROUPED_PARAMETER_UPDATE ; 
 int /*<<< orphan*/  REG_GROUPED_PARAMETER_HOLD ; 
 int /*<<< orphan*/  REG_TEST_PATTERN_MODE ; 
 int TEST_OFF ; 
 TYPE_2__* mt9p012_client ; 
 scalar_t__ mt9p012_i2c_write_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mt9p012_i2c_write_w_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ mt9p012_regs ; 

__attribute__((used)) static int32_t mt9p012_test(enum mt9p012_test_mode mo)
{
	int32_t rc = 0;

	rc = mt9p012_i2c_write_w(mt9p012_client->addr,
		REG_GROUPED_PARAMETER_HOLD,
		GROUPED_PARAMETER_HOLD);
	if (rc < 0)
		return rc;

	if (mo == TEST_OFF)
		return 0;
	else {
		rc = mt9p012_i2c_write_w_table(mt9p012_regs.ttbl, mt9p012_regs.ttbl_size);
		if (rc < 0)
			return rc;

		rc = mt9p012_i2c_write_w(mt9p012_client->addr,
				REG_TEST_PATTERN_MODE, (uint16_t)mo);
		if (rc < 0)
			return rc;
	}

	rc = mt9p012_i2c_write_w(mt9p012_client->addr,
		REG_GROUPED_PARAMETER_HOLD,
		GROUPED_PARAMETER_UPDATE);
	if (rc < 0)
		return rc;

	return rc;
}