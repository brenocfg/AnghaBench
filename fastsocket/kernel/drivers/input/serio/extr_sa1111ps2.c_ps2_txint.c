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
struct ps2if {size_t head; size_t tail; int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/ * buf; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int PS2STAT_TXE ; 
 scalar_t__ SA1111_PS2DATA ; 
 scalar_t__ SA1111_PS2STAT ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 unsigned int sa1111_readl (scalar_t__) ; 
 int /*<<< orphan*/  sa1111_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ps2_txint(int irq, void *dev_id)
{
	struct ps2if *ps2if = dev_id;
	unsigned int status;

	spin_lock(&ps2if->lock);
	status = sa1111_readl(ps2if->base + SA1111_PS2STAT);
	if (ps2if->head == ps2if->tail) {
		disable_irq_nosync(irq);
		/* done */
	} else if (status & PS2STAT_TXE) {
		sa1111_writel(ps2if->buf[ps2if->tail], ps2if->base + SA1111_PS2DATA);
		ps2if->tail = (ps2if->tail + 1) & (sizeof(ps2if->buf) - 1);
	}
	spin_unlock(&ps2if->lock);

	return IRQ_HANDLED;
}