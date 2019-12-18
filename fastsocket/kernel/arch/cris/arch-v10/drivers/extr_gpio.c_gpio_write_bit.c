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
struct gpio_private {int* port; int /*<<< orphan*/  clk_mask; int /*<<< orphan*/ * shadow; int /*<<< orphan*/  data_mask; } ;

/* Variables and functions */

__attribute__((used)) static void gpio_write_bit(struct gpio_private *priv,
	unsigned char data, int bit)
{
	*priv->port = *priv->shadow &= ~(priv->clk_mask);
	if (data & 1 << bit)
		*priv->port = *priv->shadow |= priv->data_mask;
	else
		*priv->port = *priv->shadow &= ~(priv->data_mask);

	/* For FPGA: min 5.0ns (DCC) before CCLK high */
	*priv->port = *priv->shadow |= priv->clk_mask;
}