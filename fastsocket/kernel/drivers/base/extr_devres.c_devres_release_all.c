#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct device {TYPE_1__ devres_head; int /*<<< orphan*/  devres_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int release_nodes (struct device*,int /*<<< orphan*/ *,TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 

int devres_release_all(struct device *dev)
{
	unsigned long flags;

	/* Looks like an uninitialized device structure */
	if (WARN_ON(dev->devres_head.next == NULL))
		return -ENODEV;
	spin_lock_irqsave(&dev->devres_lock, flags);
	return release_nodes(dev, dev->devres_head.next, &dev->devres_head,
			     flags);
}