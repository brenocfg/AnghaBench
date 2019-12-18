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
struct TYPE_2__ {int /*<<< orphan*/  list; scalar_t__ map; int /*<<< orphan*/  timer; } ;
struct mthca_dev {TYPE_1__ catas_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  catas_lock ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void mthca_stop_catas_poll(struct mthca_dev *dev)
{
	del_timer_sync(&dev->catas_err.timer);

	if (dev->catas_err.map)
		iounmap(dev->catas_err.map);

	spin_lock_irq(&catas_lock);
	list_del(&dev->catas_err.list);
	spin_unlock_irq(&catas_lock);
}