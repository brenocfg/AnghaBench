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
struct hvcs_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  todo_mask; int /*<<< orphan*/  vdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HVCS_SCHED_READ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hvcs_kick () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vio_disable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hvcs_handle_interrupt(int irq, void *dev_instance)
{
	struct hvcs_struct *hvcsd = dev_instance;

	spin_lock(&hvcsd->lock);
	vio_disable_interrupts(hvcsd->vdev);
	hvcsd->todo_mask |= HVCS_SCHED_READ;
	spin_unlock(&hvcsd->lock);
	hvcs_kick();

	return IRQ_HANDLED;
}