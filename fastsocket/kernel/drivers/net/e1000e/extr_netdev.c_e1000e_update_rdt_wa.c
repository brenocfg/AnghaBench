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
 int E1000_RCTL_EN ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  __ew32_prepare (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_err (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000e_update_rdt_wa(struct e1000_ring *rx_ring, unsigned int i)
{
	struct e1000_adapter *adapter = rx_ring->adapter;
	struct e1000_hw *hw = &adapter->hw;
	s32 ret_val = __ew32_prepare(hw);

	writel(i, rx_ring->tail);

	if (unlikely(!ret_val && (i != readl(rx_ring->tail)))) {
		u32 rctl = er32(RCTL);
		ew32(RCTL, rctl & ~E1000_RCTL_EN);
		e_err("ME firmware caused invalid RDT - resetting\n");
		schedule_work(&adapter->reset_task);
	}
}