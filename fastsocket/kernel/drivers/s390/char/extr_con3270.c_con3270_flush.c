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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct con3270 {scalar_t__ update_flags; TYPE_1__ view; scalar_t__ nr_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  con3270_rebuild_update (struct con3270*) ; 
 int /*<<< orphan*/  con3270_update (struct con3270*) ; 
 int /*<<< orphan*/  con3270_update_status (struct con3270*) ; 
 int /*<<< orphan*/  con3270_wait_write (struct con3270*) ; 
 struct con3270* condev ; 
 int /*<<< orphan*/  raw3270_pm_unfreeze (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
con3270_flush(void)
{
	struct con3270 *cp;
	unsigned long flags;

	cp = condev;
	if (!cp->view.dev)
		return;
	raw3270_pm_unfreeze(&cp->view);
	spin_lock_irqsave(&cp->view.lock, flags);
	con3270_wait_write(cp);
	cp->nr_up = 0;
	con3270_rebuild_update(cp);
	con3270_update_status(cp);
	while (cp->update_flags != 0) {
		spin_unlock_irqrestore(&cp->view.lock, flags);
		con3270_update(cp);
		spin_lock_irqsave(&cp->view.lock, flags);
		con3270_wait_write(cp);
	}
	spin_unlock_irqrestore(&cp->view.lock, flags);
}