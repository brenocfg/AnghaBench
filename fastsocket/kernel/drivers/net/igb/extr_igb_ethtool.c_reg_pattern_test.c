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
typedef  int u64 ;
typedef  int u32 ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {TYPE_1__* pdev; struct e1000_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int const) ; 
 int rd32 (int) ; 
 int /*<<< orphan*/  wr32 (int,int const) ; 

__attribute__((used)) static bool reg_pattern_test(struct igb_adapter *adapter, u64 *data,
			     int reg, u32 mask, u32 write)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 pat, val;
	static const u32 _test[] =
		{0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF};
	for (pat = 0; pat < ARRAY_SIZE(_test); pat++) {
		wr32(reg, (_test[pat] & write));
		val = rd32(reg) & mask;
		if (val != (_test[pat] & write & mask)) {
			dev_err(&adapter->pdev->dev,
				"pattern test reg %04X failed: got 0x%08X expected 0x%08X\n",
				reg, val, (_test[pat] & write & mask));
			*data = reg;
			return 1;
		}
	}

	return 0;
}