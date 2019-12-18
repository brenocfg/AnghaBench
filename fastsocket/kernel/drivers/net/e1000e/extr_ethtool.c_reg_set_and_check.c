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
typedef  int u64 ;
typedef  int u32 ;
struct e1000_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int __er32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __ew32 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  e_err (char*,int,int,int) ; 

__attribute__((used)) static bool reg_set_and_check(struct e1000_adapter *adapter, u64 *data,
			      int reg, u32 mask, u32 write)
{
	u32 val;
	__ew32(&adapter->hw, reg, write & mask);
	val = __er32(&adapter->hw, reg);
	if ((write & mask) != (val & mask)) {
		e_err("set/check test failed (reg 0x%05X): got 0x%08X expected 0x%08X\n",
		      reg, (val & mask), (write & mask));
		*data = reg;
		return 1;
	}
	return 0;
}