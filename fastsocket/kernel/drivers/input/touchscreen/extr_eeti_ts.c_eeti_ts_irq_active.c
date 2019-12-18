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
struct eeti_ts_priv {scalar_t__ irq_active_high; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_gpio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int eeti_ts_irq_active(struct eeti_ts_priv *priv)
{
	return gpio_get_value(irq_to_gpio(priv->irq)) == priv->irq_active_high;
}