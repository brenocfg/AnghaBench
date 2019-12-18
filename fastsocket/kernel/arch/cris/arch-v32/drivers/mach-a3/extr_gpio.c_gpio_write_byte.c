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
struct gpio_private {int /*<<< orphan*/  data_mask; int /*<<< orphan*/  clk_mask; scalar_t__ write_msb; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_write_bit (unsigned long*,unsigned char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_write_byte(struct gpio_private *priv, unsigned long *port,
		unsigned char data)
{
	int i;

	if (priv->write_msb)
		for (i = 7; i >= 0; i--)
			gpio_write_bit(port, data, i, priv->clk_mask,
				priv->data_mask);
	else
		for (i = 0; i <= 7; i++)
			gpio_write_bit(port, data, i, priv->clk_mask,
				priv->data_mask);
}