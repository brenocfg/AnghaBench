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
struct talitos_private {int /*<<< orphan*/  done_task; scalar_t__ reg; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ TALITOS_ICR ; 
 scalar_t__ TALITOS_ICR_LO ; 
 scalar_t__ TALITOS_IMR ; 
 int /*<<< orphan*/  TALITOS_IMR_DONE ; 
 scalar_t__ TALITOS_ISR ; 
 int TALITOS_ISR_CHDONE ; 
 scalar_t__ TALITOS_ISR_LO ; 
 int /*<<< orphan*/  clrbits32 (scalar_t__,int /*<<< orphan*/ ) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int in_be32 (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 
 int /*<<< orphan*/  talitos_error (unsigned long,int,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t talitos_interrupt(int irq, void *data)
{
	struct device *dev = data;
	struct talitos_private *priv = dev_get_drvdata(dev);
	u32 isr, isr_lo;

	isr = in_be32(priv->reg + TALITOS_ISR);
	isr_lo = in_be32(priv->reg + TALITOS_ISR_LO);
	/* Acknowledge interrupt */
	out_be32(priv->reg + TALITOS_ICR, isr);
	out_be32(priv->reg + TALITOS_ICR_LO, isr_lo);

	if (unlikely((isr & ~TALITOS_ISR_CHDONE) || isr_lo))
		talitos_error((unsigned long)data, isr, isr_lo);
	else
		if (likely(isr & TALITOS_ISR_CHDONE)) {
			/* mask further done interrupts. */
			clrbits32(priv->reg + TALITOS_IMR, TALITOS_IMR_DONE);
			/* done_task will unmask done interrupts at exit */
			tasklet_schedule(&priv->done_task);
		}

	return (isr || isr_lo) ? IRQ_HANDLED : IRQ_NONE;
}