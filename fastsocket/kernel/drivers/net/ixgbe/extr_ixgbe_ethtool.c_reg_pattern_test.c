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
struct TYPE_2__ {scalar_t__ hw_addr; } ;
struct ixgbe_adapter {TYPE_1__ hw; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,int,int,int const) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int const,scalar_t__) ; 

__attribute__((used)) static bool reg_pattern_test(struct ixgbe_adapter *adapter, u64 *data, int reg,
			     u32 mask, u32 write)
{
	u32 pat, val, before;
	static const u32 test_pattern[] = {
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF};

	for (pat = 0; pat < ARRAY_SIZE(test_pattern); pat++) {
		before = readl(adapter->hw.hw_addr + reg);
		writel((test_pattern[pat] & write),
		       (adapter->hw.hw_addr + reg));
		val = readl(adapter->hw.hw_addr + reg);
		if (val != (test_pattern[pat] & write & mask)) {
			e_err(drv, "pattern test reg %04X failed: got "
			      "0x%08X expected 0x%08X\n",
			      reg, val, (test_pattern[pat] & write & mask));
			*data = reg;
			writel(before, adapter->hw.hw_addr + reg);
			return 1;
		}
		writel(before, adapter->hw.hw_addr + reg);
	}
	return 0;
}