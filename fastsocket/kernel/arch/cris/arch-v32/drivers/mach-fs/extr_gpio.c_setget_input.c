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
 size_t GPIO_MINOR_A ; 
 size_t GPIO_MINOR_V ; 
 unsigned long* changeable_dir ; 
 unsigned long** dir_oe ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

inline unsigned long setget_input(struct gpio_private *priv, unsigned long arg)
{
	/* Set direction 0=unchanged 1=input,
	 * return mask with 1=input
	 */
	unsigned long flags;
	unsigned long dir_shadow;

	local_irq_save(flags);
	dir_shadow = *dir_oe[priv->minor];
	dir_shadow &= ~(arg & changeable_dir[priv->minor]);
	*dir_oe[priv->minor] = dir_shadow;
	local_irq_restore(flags);

	if (priv->minor == GPIO_MINOR_A)
		dir_shadow ^= 0xFF;    /* Only 8 bits */
#ifdef CONFIG_ETRAX_VIRTUAL_GPIO
	else if (priv->minor == GPIO_MINOR_V)
		dir_shadow ^= 0xFFFF;  /* Only 16 bits */
#endif
	else
		dir_shadow ^= 0x3FFFF; /* Only 18 bits */
	return dir_shadow;

}