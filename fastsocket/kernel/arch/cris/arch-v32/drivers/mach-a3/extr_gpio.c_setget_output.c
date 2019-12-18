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
 unsigned long* changeable_dir ; 
 int /*<<< orphan*/ * dir_oe ; 
 int /*<<< orphan*/  gpio_lock ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long setget_output(struct gpio_private *priv,
	unsigned long arg)
{
	unsigned long flags;
	unsigned long dir_shadow;

	spin_lock_irqsave(&gpio_lock, flags);

	dir_shadow = readl(dir_oe[priv->minor]) |
		(arg & changeable_dir[priv->minor]);
	writel(dir_shadow, dir_oe[priv->minor]);

	spin_unlock_irqrestore(&gpio_lock, flags);
	return dir_shadow;
}