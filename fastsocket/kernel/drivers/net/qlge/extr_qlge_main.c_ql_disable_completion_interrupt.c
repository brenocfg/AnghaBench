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
struct ql_adapter {int /*<<< orphan*/  hw_lock; struct intr_context* intr_context; int /*<<< orphan*/  flags; } ;
struct intr_context {int /*<<< orphan*/  irq_cnt; int /*<<< orphan*/  intr_dis_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_EN ; 
 int /*<<< orphan*/  QL_MSIX_ENABLED ; 
 int /*<<< orphan*/  STS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 ql_disable_completion_interrupt(struct ql_adapter *qdev, u32 intr)
{
	u32 var = 0;
	struct intr_context *ctx;

	/* HW disables for us if we're MSIX multi interrupts and
	 * it's not the default (zeroeth) interrupt.
	 */
	if (likely(test_bit(QL_MSIX_ENABLED, &qdev->flags) && intr))
		return 0;

	ctx = qdev->intr_context + intr;
	spin_lock(&qdev->hw_lock);
	if (!atomic_read(&ctx->irq_cnt)) {
		ql_write32(qdev, INTR_EN,
		ctx->intr_dis_mask);
		var = ql_read32(qdev, STS);
	}
	atomic_inc(&ctx->irq_cnt);
	spin_unlock(&qdev->hw_lock);
	return var;
}