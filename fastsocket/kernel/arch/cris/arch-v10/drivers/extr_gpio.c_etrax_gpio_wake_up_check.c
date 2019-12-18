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
struct gpio_private {unsigned long* port; scalar_t__ minor; unsigned long highalarm; unsigned long lowalarm; struct gpio_private* next; int /*<<< orphan*/  alarm_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ) ; 
 scalar_t__ GPIO_MINOR_G ; 
 unsigned long* R_PORT_G_DATA ; 
 scalar_t__ USE_PORTS (struct gpio_private*) ; 
 struct gpio_private* alarmlist ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  printk (char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int etrax_gpio_wake_up_check(void)
{
	struct gpio_private *priv;
	unsigned long data = 0;
        int ret = 0;
	unsigned long flags;

	spin_lock_irqsave(&gpio_lock, flags);
	priv = alarmlist;
	while (priv) {
		if (USE_PORTS(priv))
			data = *priv->port;
		else if (priv->minor == GPIO_MINOR_G)
			data = *R_PORT_G_DATA;

		if ((data & priv->highalarm) ||
		    (~data & priv->lowalarm)) {
			DP(printk("etrax_gpio_wake_up_check %i\n",priv->minor));
			wake_up_interruptible(&priv->alarm_wq);
                        ret = 1;
		}
		priv = priv->next;
	}
	spin_unlock_irqrestore(&gpio_lock, flags);
        return ret;
}