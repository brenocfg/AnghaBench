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
typedef  struct net_device* u32 ;
struct ns83820 {scalar_t__ base; scalar_t__ ihr; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ ISR ; 
 struct ns83820* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  dprintk (char*,struct net_device*) ; 
 int /*<<< orphan*/  ns83820_do_isr (struct net_device*,struct net_device*) ; 
 struct net_device* readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t ns83820_irq(int foo, void *data)
{
	struct net_device *ndev = data;
	struct ns83820 *dev = PRIV(ndev);
	u32 isr;
	dprintk("ns83820_irq(%p)\n", ndev);

	dev->ihr = 0;

	isr = readl(dev->base + ISR);
	dprintk("irq: %08x\n", isr);
	ns83820_do_isr(ndev, isr);
	return IRQ_HANDLED;
}