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
struct net_device {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 

__attribute__((used)) static int ibmlana_close(struct net_device *dev)
{
	/* turn off board */

	/* release resources */
	if (dev->irq != 0)
		free_irq(dev->irq, dev);
	dev->irq = 0;
	return 0;
}