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
struct net_device {int /*<<< orphan*/  irq; } ;
struct happy_meal {int happy_flags; int /*<<< orphan*/  happy_lock; int /*<<< orphan*/  happy_timer; int /*<<< orphan*/  gregs; } ;

/* Variables and functions */
 int HFLAG_PCI ; 
 int HFLAG_QUATTRO ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  happy_meal_clean_rings (struct happy_meal*) ; 
 int /*<<< orphan*/  happy_meal_stop (struct happy_meal*,int /*<<< orphan*/ ) ; 
 struct happy_meal* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int happy_meal_close(struct net_device *dev)
{
	struct happy_meal *hp = netdev_priv(dev);

	spin_lock_irq(&hp->happy_lock);
	happy_meal_stop(hp, hp->gregs);
	happy_meal_clean_rings(hp);

	/* If auto-negotiation timer is running, kill it. */
	del_timer(&hp->happy_timer);

	spin_unlock_irq(&hp->happy_lock);

	/* On Quattro QFE cards, all hme interrupts are concentrated
	 * into a single source which we register handling at probe
	 * time and never unregister.
	 */
	if ((hp->happy_flags & (HFLAG_QUATTRO|HFLAG_PCI)) != HFLAG_QUATTRO)
		free_irq(dev->irq, dev);

	return 0;
}