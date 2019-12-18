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
struct migor_ts_priv {int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t migor_ts_isr(int irq, void *dev_id)
{
	struct migor_ts_priv *priv = dev_id;

	/* the touch screen controller chip is hooked up to the cpu
	 * using i2c and a single interrupt line. the interrupt line
	 * is pulled low whenever someone taps the screen. to deassert
	 * the interrupt line we need to acknowledge the interrupt by
	 * communicating with the controller over the slow i2c bus.
	 *
	 * we can't acknowledge from interrupt context since the i2c
	 * bus controller may sleep, so we just disable the interrupt
	 * here and handle the acknowledge using delayed work.
	 */

	disable_irq_nosync(irq);
	schedule_delayed_work(&priv->work, HZ / 20);

	return IRQ_HANDLED;
}