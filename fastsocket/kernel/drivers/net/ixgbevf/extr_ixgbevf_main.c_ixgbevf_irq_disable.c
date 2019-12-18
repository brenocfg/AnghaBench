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
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int num_msix_vectors; TYPE_1__* msix_entries; struct ixgbe_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VTEIAC ; 
 int /*<<< orphan*/  IXGBE_VTEIAM ; 
 int /*<<< orphan*/  IXGBE_VTEIMC ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ixgbevf_irq_disable(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int i;

	IXGBE_WRITE_REG(hw, IXGBE_VTEIAM, 0);
	IXGBE_WRITE_REG(hw, IXGBE_VTEIMC, ~0);
	IXGBE_WRITE_REG(hw, IXGBE_VTEIAC, 0);

	IXGBE_WRITE_FLUSH(hw);

	for (i = 0; i < adapter->num_msix_vectors; i++)
		synchronize_irq(adapter->msix_entries[i].vector);
}