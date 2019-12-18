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
struct cpci_hp_controller {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_id; scalar_t__ irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cleanup_slots () ; 
 TYPE_1__* controller ; 
 int /*<<< orphan*/  cpci_stop_thread () ; 
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_finished ; 

int
cpci_hp_unregister_controller(struct cpci_hp_controller *old_controller)
{
	int status = 0;

	if (controller) {
		if (!thread_finished)
			cpci_stop_thread();
		if (controller->irq)
			free_irq(controller->irq, controller->dev_id);
		controller = NULL;
		cleanup_slots();
	} else
		status = -ENODEV;
	return status;
}