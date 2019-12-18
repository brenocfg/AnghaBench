#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int clr_mask; TYPE_4__* eq; scalar_t__ clr_int; } ;
struct TYPE_6__ {scalar_t__ ecr_base; } ;
struct TYPE_7__ {TYPE_1__ tavor; } ;
struct mthca_dev {TYPE_3__ eq_table; TYPE_2__ eq_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_9__ {int eqn_mask; int /*<<< orphan*/  eqn; int /*<<< orphan*/  cons_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MTHCA_ECR_BASE ; 
 scalar_t__ MTHCA_ECR_CLR_BASE ; 
 int MTHCA_NUM_EQ ; 
 scalar_t__ mthca_eq_int (struct mthca_dev*,TYPE_4__*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  tavor_eq_req_not (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tavor_set_eq_ci (struct mthca_dev*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mthca_tavor_interrupt(int irq, void *dev_ptr)
{
	struct mthca_dev *dev = dev_ptr;
	u32 ecr;
	int i;

	if (dev->eq_table.clr_mask)
		writel(dev->eq_table.clr_mask, dev->eq_table.clr_int);

	ecr = readl(dev->eq_regs.tavor.ecr_base + 4);
	if (!ecr)
		return IRQ_NONE;

	writel(ecr, dev->eq_regs.tavor.ecr_base +
	       MTHCA_ECR_CLR_BASE - MTHCA_ECR_BASE + 4);

	for (i = 0; i < MTHCA_NUM_EQ; ++i)
		if (ecr & dev->eq_table.eq[i].eqn_mask) {
			if (mthca_eq_int(dev, &dev->eq_table.eq[i]))
				tavor_set_eq_ci(dev, &dev->eq_table.eq[i],
						dev->eq_table.eq[i].cons_index);
			tavor_eq_req_not(dev, dev->eq_table.eq[i].eqn);
		}

	return IRQ_HANDLED;
}