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
struct inode {int dummy; } ;
struct gpio_private {scalar_t__ minor; int lowalarm; unsigned long highalarm; struct gpio_private* next; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int CONFIG_ETRAX_VIRTUAL_GPIO_INTERRUPT_PA_PIN ; 
 scalar_t__ GPIO_MINOR_A ; 
 int /*<<< orphan*/  alarm_lock ; 
 struct gpio_private* alarmlist ; 
 unsigned long gpio_pa_high_alarms ; 
 unsigned long gpio_pa_low_alarms ; 
 unsigned long gpio_some_alarms ; 
 int /*<<< orphan*/  kfree (struct gpio_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpio_release(struct inode *inode, struct file *filp)
{
	struct gpio_private *p;
	struct gpio_private *todel;
	/* local copies while updating them: */
	unsigned long a_high, a_low;
	unsigned long some_alarms;

	/* unlink from alarmlist and free the private structure */

	spin_lock_irq(&alarm_lock);
	p = alarmlist;
	todel = (struct gpio_private *)filp->private_data;

	if (p == todel) {
		alarmlist = todel->next;
	} else {
		while (p->next != todel)
			p = p->next;
		p->next = todel->next;
	}

	kfree(todel);
	/* Check if there are still any alarms set */
	p = alarmlist;
	some_alarms = 0;
	a_high = 0;
	a_low = 0;
	while (p) {
		if (p->minor == GPIO_MINOR_A) {
#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
			p->lowalarm |= (1 << CONFIG_ETRAX_VIRTUAL_GPIO_INTERRUPT_PA_PIN);
#endif
			a_high |= p->highalarm;
			a_low |= p->lowalarm;
		}

		if (p->highalarm | p->lowalarm)
			some_alarms = 1;
		p = p->next;
	}

#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	/* Variables 'some_alarms' and 'a_low' needs to be set here again
	 * to ensure that interrupt for virtual GPIO is handled.
	 */
	some_alarms = 1;
	a_low |= (1 << CONFIG_ETRAX_VIRTUAL_GPIO_INTERRUPT_PA_PIN);
#endif

	gpio_some_alarms = some_alarms;
	gpio_pa_high_alarms = a_high;
	gpio_pa_low_alarms = a_low;
	spin_unlock_irq(&alarm_lock);

	return 0;
}