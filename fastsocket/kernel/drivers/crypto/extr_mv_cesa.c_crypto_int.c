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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ eng_st; int /*<<< orphan*/  queue_th; scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ ENGINE_BUSY ; 
 scalar_t__ ENGINE_W_DEQUEUE ; 
 scalar_t__ FPGA_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ SEC_ACCEL_INT_STATUS ; 
 int SEC_INT_ACCEL0_DONE ; 
 TYPE_1__* cpg ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

irqreturn_t crypto_int(int irq, void *priv)
{
	u32 val;

	val = readl(cpg->reg + SEC_ACCEL_INT_STATUS);
	if (!(val & SEC_INT_ACCEL0_DONE))
		return IRQ_NONE;

	val &= ~SEC_INT_ACCEL0_DONE;
	writel(val, cpg->reg + FPGA_INT_STATUS);
	writel(val, cpg->reg + SEC_ACCEL_INT_STATUS);
	BUG_ON(cpg->eng_st != ENGINE_BUSY);
	cpg->eng_st = ENGINE_W_DEQUEUE;
	wake_up_process(cpg->queue_th);
	return IRQ_HANDLED;
}