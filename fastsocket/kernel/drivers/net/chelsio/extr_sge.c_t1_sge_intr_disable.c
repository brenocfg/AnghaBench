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
typedef  int u32 ;
struct sge {TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_PL_ENABLE ; 
 scalar_t__ A_SG_INT_ENABLE ; 
 int SGE_PL_INTR_MASK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void t1_sge_intr_disable(struct sge *sge)
{
	u32 val = readl(sge->adapter->regs + A_PL_ENABLE);

	writel(val & ~SGE_PL_INTR_MASK, sge->adapter->regs + A_PL_ENABLE);
	writel(0, sge->adapter->regs + A_SG_INT_ENABLE);
}