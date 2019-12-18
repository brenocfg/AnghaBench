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
struct gpio_private {int minor; struct gpio_private* next; int /*<<< orphan*/  alarm_wq; scalar_t__ lowalarm; scalar_t__ highalarm; scalar_t__ data_mask; scalar_t__ clk_mask; } ;
struct file {struct gpio_private* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIO_MINOR_LAST ; 
 int GPIO_MINOR_LAST_PWM ; 
 int GPIO_MINOR_PWM0 ; 
 struct gpio_private* alarmlist ; 
 int /*<<< orphan*/  gpio_lock ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct gpio_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  memset (struct gpio_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int gpio_open(struct inode *inode, struct file *filp)
{
	struct gpio_private *priv;
	int p = iminor(inode);

	if (p > GPIO_MINOR_LAST_PWM ||
	    (p > GPIO_MINOR_LAST && p < GPIO_MINOR_PWM0))
		return -EINVAL;

	priv = kmalloc(sizeof(struct gpio_private), GFP_KERNEL);

	if (!priv)
		return -ENOMEM;

	lock_kernel();
	memset(priv, 0, sizeof(*priv));

	priv->minor = p;
	filp->private_data = priv;

	/* initialize the io/alarm struct, not for PWM ports though  */
	if (p <= GPIO_MINOR_LAST) {

		priv->clk_mask = 0;
		priv->data_mask = 0;
		priv->highalarm = 0;
		priv->lowalarm = 0;

		init_waitqueue_head(&priv->alarm_wq);

		/* link it into our alarmlist */
		spin_lock_irq(&gpio_lock);
		priv->next = alarmlist;
		alarmlist = priv;
		spin_unlock_irq(&gpio_lock);
	}

	unlock_kernel();
	return 0;
}