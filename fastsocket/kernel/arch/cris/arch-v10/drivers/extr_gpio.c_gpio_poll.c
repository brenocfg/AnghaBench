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
struct gpio_private {scalar_t__ minor; unsigned long highalarm; unsigned long lowalarm; int /*<<< orphan*/  alarm_wq; } ;
struct file {struct gpio_private* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ) ; 
 scalar_t__ GPIO_MINOR_A ; 
 scalar_t__ GPIO_MINOR_B ; 
 scalar_t__ GPIO_MINOR_G ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 unsigned long* R_IRQ_MASK1_SET ; 
 unsigned long R_IRQ_MASK1_SET__pa0__BITNR ; 
 unsigned long* R_PORT_G_DATA ; 
 unsigned long* R_PORT_PA_DATA ; 
 unsigned long* R_PORT_PB_DATA ; 
 int /*<<< orphan*/  gpio_lock ; 
 unsigned long gpio_pa_irq_enabled_mask ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int gpio_poll(struct file *file, poll_table *wait)
{
	unsigned int mask = 0;
	struct gpio_private *priv = file->private_data;
	unsigned long data;
	unsigned long flags;

	spin_lock_irqsave(&gpio_lock, flags);

	poll_wait(file, &priv->alarm_wq, wait);
	if (priv->minor == GPIO_MINOR_A) {
		unsigned long tmp;
		data = *R_PORT_PA_DATA;
		/* PA has support for high level interrupt -
		 * lets activate for those low and with highalarm set
		 */
		tmp = ~data & priv->highalarm & 0xFF;
		tmp = (tmp << R_IRQ_MASK1_SET__pa0__BITNR);

		gpio_pa_irq_enabled_mask |= tmp;
		*R_IRQ_MASK1_SET = tmp;
	} else if (priv->minor == GPIO_MINOR_B)
		data = *R_PORT_PB_DATA;
	else if (priv->minor == GPIO_MINOR_G)
		data = *R_PORT_G_DATA;
	else {
		mask = 0;
		goto out;
	}

	if ((data & priv->highalarm) ||
	    (~data & priv->lowalarm)) {
		mask = POLLIN|POLLRDNORM;
	}

out:
	spin_unlock_irqrestore(&gpio_lock, flags);
	DP(printk("gpio_poll ready: mask 0x%08X\n", mask));

	return mask;
}