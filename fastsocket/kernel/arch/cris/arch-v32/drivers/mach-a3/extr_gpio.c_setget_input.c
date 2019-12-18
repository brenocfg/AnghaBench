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
struct gpio_private {size_t minor; } ;

/* Variables and functions */
 size_t GPIO_MINOR_C ; 
 size_t GPIO_MINOR_V ; 
 unsigned long* changeable_dir ; 
 int /*<<< orphan*/ * dir_oe ; 
 int /*<<< orphan*/  gpio_lock ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

inline unsigned long setget_input(struct gpio_private *priv, unsigned long arg)
{
	/* Set direction 0=unchanged 1=input,
	 * return mask with 1=input
	 */
	unsigned long flags;
	unsigned long dir_shadow;

	spin_lock_irqsave(&gpio_lock, flags);

	dir_shadow = readl(dir_oe[priv->minor]) &
		~(arg & changeable_dir[priv->minor]);
	writel(dir_shadow, dir_oe[priv->minor]);

	spin_unlock_irqrestore(&gpio_lock, flags);

	if (priv->minor == GPIO_MINOR_C)
		dir_shadow ^= 0xFFFF;		/* Only 16 bits */
#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	else if (priv->minor == GPIO_MINOR_V)
		dir_shadow ^= 0xFFFF;		/* Only 16 bits */
#endif
	else
		dir_shadow ^= 0xFFFFFFFF;	/* PA, PB and PD 32 bits */

	return dir_shadow;

}