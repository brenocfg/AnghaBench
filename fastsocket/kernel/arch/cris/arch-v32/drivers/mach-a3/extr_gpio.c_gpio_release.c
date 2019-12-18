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
struct file {struct gpio_private* private_data; } ;

/* Variables and functions */
 int CONFIG_ETRAX_VIRTUAL_GPIO_INTERRUPT_PA_PIN ; 
 scalar_t__ GPIO_MINOR_A ; 
 scalar_t__ GPIO_MINOR_LAST ; 
 struct gpio_private* alarmlist ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  kfree (struct gpio_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_release(struct inode *inode, struct file *filp)
{
	struct gpio_private *p;
	struct gpio_private *todel;
	/* local copies while updating them: */
	unsigned long a_high, a_low;

	/* prepare to free private structure */
	todel = filp->private_data;

	/* unlink from alarmlist - only for non-PWM ports though */
	if (todel->minor <= GPIO_MINOR_LAST) {
		spin_lock_irq(&gpio_lock);
		p = alarmlist;

		if (p == todel)
			alarmlist = todel->next;
		 else {
			while (p->next != todel)
				p = p->next;
			p->next = todel->next;
		}

		/* Check if there are still any alarms set */
		p = alarmlist;
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

			p = p->next;
		}

#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	/* Variable 'a_low' needs to be set here again
	 * to ensure that interrupt for virtual GPIO is handled.
	 */
		a_low |= (1 << CONFIG_ETRAX_VIRTUAL_GPIO_INTERRUPT_PA_PIN);
#endif

		spin_unlock_irq(&gpio_lock);
	}
	kfree(todel);

	return 0;
}