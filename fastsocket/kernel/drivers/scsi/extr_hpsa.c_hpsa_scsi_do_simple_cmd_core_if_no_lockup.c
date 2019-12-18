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
struct ctlr_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  lockup_detected; } ;
struct CommandList {TYPE_1__* err_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  CommandStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_HARDWARE_ERR ; 
 int /*<<< orphan*/  hpsa_scsi_do_simple_cmd_core (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpsa_scsi_do_simple_cmd_core_if_no_lockup(struct ctlr_info *h,
	struct CommandList *c)
{
	unsigned long flags;

	/* If controller lockup detected, fake a hardware error. */
	spin_lock_irqsave(&h->lock, flags);
	if (unlikely(h->lockup_detected)) {
		spin_unlock_irqrestore(&h->lock, flags);
		c->err_info->CommandStatus = CMD_HARDWARE_ERR;
	} else {
		spin_unlock_irqrestore(&h->lock, flags);
		hpsa_scsi_do_simple_cmd_core(h, c);
	}
}