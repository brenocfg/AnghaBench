#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct ixgbe_reg_test {scalar_t__ reg; scalar_t__ array_len; int test_type; int /*<<< orphan*/  write; int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int type; } ;
struct TYPE_5__ {scalar_t__ hw_addr; TYPE_1__ mac; } ;
struct ixgbe_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ IXGBE_READ_REG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_STATUS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
#define  PATTERN_TEST 136 
 int /*<<< orphan*/  REG_PATTERN_TEST (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_AND_CHECK (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SET_READ_TEST 135 
#define  TABLE32_TEST 134 
#define  TABLE64_TEST_HI 133 
#define  TABLE64_TEST_LO 132 
#define  WRITE_NO_TEST 131 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
#define  ixgbe_mac_82598EB 130 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 struct ixgbe_reg_test* reg_test_82598 ; 
 struct ixgbe_reg_test* reg_test_82599 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ixgbe_reg_test(struct ixgbe_adapter *adapter, u64 *data)
{
	const struct ixgbe_reg_test *test;
	u32 value, before, after;
	u32 i, toggle;

	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82598EB:
		toggle = 0x7FFFF3FF;
		test = reg_test_82598;
		break;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
		toggle = 0x7FFFF30F;
		test = reg_test_82599;
		break;
	default:
		*data = 1;
		return 1;
		break;
	}

	/*
	 * Because the status register is such a special case,
	 * we handle it separately from the rest of the register
	 * tests.  Some bits are read-only, some toggle, and some
	 * are writeable on newer MACs.
	 */
	before = IXGBE_READ_REG(&adapter->hw, IXGBE_STATUS);
	value = (IXGBE_READ_REG(&adapter->hw, IXGBE_STATUS) & toggle);
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_STATUS, toggle);
	after = IXGBE_READ_REG(&adapter->hw, IXGBE_STATUS) & toggle;
	if (value != after) {
		e_err(drv, "failed STATUS register test got: 0x%08X "
		      "expected: 0x%08X\n", after, value);
		*data = 1;
		return 1;
	}
	/* restore previous status */
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_STATUS, before);

	/*
	 * Perform the remainder of the register test, looping through
	 * the test table until we either fail or reach the null entry.
	 */
	while (test->reg) {
		for (i = 0; i < test->array_len; i++) {
			switch (test->test_type) {
			case PATTERN_TEST:
				REG_PATTERN_TEST(test->reg + (i * 0x40),
						 test->mask,
						 test->write);
				break;
			case SET_READ_TEST:
				REG_SET_AND_CHECK(test->reg + (i * 0x40),
						  test->mask,
						  test->write);
				break;
			case WRITE_NO_TEST:
				writel(test->write,
				       (adapter->hw.hw_addr + test->reg)
				       + (i * 0x40));
				break;
			case TABLE32_TEST:
				REG_PATTERN_TEST(test->reg + (i * 4),
						 test->mask,
						 test->write);
				break;
			case TABLE64_TEST_LO:
				REG_PATTERN_TEST(test->reg + (i * 8),
						 test->mask,
						 test->write);
				break;
			case TABLE64_TEST_HI:
				REG_PATTERN_TEST((test->reg + 4) + (i * 8),
						 test->mask,
						 test->write);
				break;
			}
		}
		test++;
	}

	*data = 0;
	return 0;
}