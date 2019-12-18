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
struct atl1e_adapter {int /*<<< orphan*/  hw; int /*<<< orphan*/  irq_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_FLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AT_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_IMR ; 
 int /*<<< orphan*/  REG_ISR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atl1e_irq_reset(struct atl1e_adapter *adapter)
{
	atomic_set(&adapter->irq_sem, 0);
	AT_WRITE_REG(&adapter->hw, REG_ISR, 0);
	AT_WRITE_REG(&adapter->hw, REG_IMR, 0);
	AT_WRITE_FLUSH(&adapter->hw);
}