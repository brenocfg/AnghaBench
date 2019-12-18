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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct happy_meal {int /*<<< orphan*/  happy_lock; scalar_t__ gregs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ GREG_STAT ; 
 int GREG_STAT_ERRORS ; 
 int GREG_STAT_MIFIRQ ; 
 int GREG_STAT_RXTOHOST ; 
 int GREG_STAT_TXALL ; 
 int /*<<< orphan*/  HMD (char*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ happy_meal_is_not_so_happy (struct happy_meal*,int) ; 
 int /*<<< orphan*/  happy_meal_mif_interrupt (struct happy_meal*) ; 
 int /*<<< orphan*/  happy_meal_rx (struct happy_meal*,struct net_device*) ; 
 int /*<<< orphan*/  happy_meal_tx (struct happy_meal*) ; 
 int hme_read32 (struct happy_meal*,scalar_t__) ; 
 struct happy_meal* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t happy_meal_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct happy_meal *hp  = netdev_priv(dev);
	u32 happy_status       = hme_read32(hp, hp->gregs + GREG_STAT);

	HMD(("happy_meal_interrupt: status=%08x ", happy_status));

	spin_lock(&hp->happy_lock);

	if (happy_status & GREG_STAT_ERRORS) {
		HMD(("ERRORS "));
		if (happy_meal_is_not_so_happy(hp, /* un- */ happy_status))
			goto out;
	}

	if (happy_status & GREG_STAT_MIFIRQ) {
		HMD(("MIFIRQ "));
		happy_meal_mif_interrupt(hp);
	}

	if (happy_status & GREG_STAT_TXALL) {
		HMD(("TXALL "));
		happy_meal_tx(hp);
	}

	if (happy_status & GREG_STAT_RXTOHOST) {
		HMD(("RXTOHOST "));
		happy_meal_rx(hp, dev);
	}

	HMD(("done\n"));
out:
	spin_unlock(&hp->happy_lock);

	return IRQ_HANDLED;
}