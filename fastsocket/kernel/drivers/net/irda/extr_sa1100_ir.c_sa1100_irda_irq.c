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
struct sa1100_irda {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ IS_FIR (struct sa1100_irda*) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sa1100_irda_fir_irq (struct net_device*) ; 
 int /*<<< orphan*/  sa1100_irda_hpsir_irq (struct net_device*) ; 

__attribute__((used)) static irqreturn_t sa1100_irda_irq(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	if (IS_FIR(((struct sa1100_irda *)netdev_priv(dev))))
		sa1100_irda_fir_irq(dev);
	else
		sa1100_irda_hpsir_irq(dev);
	return IRQ_HANDLED;
}