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
struct ti_ohci {int /*<<< orphan*/  iso_tasklet_list_lock; int /*<<< orphan*/  ir_multichannel_used; int /*<<< orphan*/  ir_ctx_usage; int /*<<< orphan*/  it_ctx_usage; } ;
struct ohci1394_iso_tasklet {scalar_t__ type; int /*<<< orphan*/  link; int /*<<< orphan*/  context; int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 scalar_t__ OHCI_ISO_MULTICHANNEL_RECEIVE ; 
 scalar_t__ OHCI_ISO_TRANSMIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void ohci1394_unregister_iso_tasklet(struct ti_ohci *ohci,
				     struct ohci1394_iso_tasklet *tasklet)
{
	unsigned long flags;

	tasklet_kill(&tasklet->tasklet);

	spin_lock_irqsave(&ohci->iso_tasklet_list_lock, flags);

	if (tasklet->type == OHCI_ISO_TRANSMIT)
		clear_bit(tasklet->context, &ohci->it_ctx_usage);
	else {
		clear_bit(tasklet->context, &ohci->ir_ctx_usage);

		if (tasklet->type == OHCI_ISO_MULTICHANNEL_RECEIVE) {
			clear_bit(0, &ohci->ir_multichannel_used);
		}
	}

	list_del(&tasklet->link);

	spin_unlock_irqrestore(&ohci->iso_tasklet_list_lock, flags);
}