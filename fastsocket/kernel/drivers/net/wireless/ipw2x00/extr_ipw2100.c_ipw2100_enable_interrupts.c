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
struct ipw2100_priv {int status; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_INTERRUPT_MASK ; 
 int /*<<< orphan*/  IPW_REG_INTA_MASK ; 
 int STATUS_INT_ENABLED ; 
 int /*<<< orphan*/  write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ipw2100_enable_interrupts(struct ipw2100_priv *priv)
{
	if (priv->status & STATUS_INT_ENABLED)
		return;
	priv->status |= STATUS_INT_ENABLED;
	write_register(priv->net_dev, IPW_REG_INTA_MASK, IPW_INTERRUPT_MASK);
}