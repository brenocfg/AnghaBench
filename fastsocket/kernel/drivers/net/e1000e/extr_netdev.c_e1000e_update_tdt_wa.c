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
typedef  int u32 ;
struct e1000_ring {int /*<<< orphan*/  tail; struct e1000_adapter* adapter; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  reset_task; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int E1000_TCTL_EN ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  __ew32_prepare (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_err (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000e_update_tdt_wa(struct e1000_ring *tx_ring, unsigned int i)
{
	struct e1000_adapter *adapter = tx_ring->adapter;
	struct e1000_hw *hw = &adapter->hw;
	s32 ret_val = __ew32_prepare(hw);

	writel(i, tx_ring->tail);

	if (unlikely(!ret_val && (i != readl(tx_ring->tail)))) {
		u32 tctl = er32(TCTL);
		ew32(TCTL, tctl & ~E1000_TCTL_EN);
		e_err("ME firmware caused invalid TDT - resetting\n");
		schedule_work(&adapter->reset_task);
	}
}