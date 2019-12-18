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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {int state; scalar_t__ reap_ref; int /*<<< orphan*/  ew; int /*<<< orphan*/  devices; TYPE_1__ dev; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  enum scsi_target_state { ____Placeholder_scsi_target_state } scsi_target_state ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int STARGET_CREATED ; 
 int STARGET_DEL ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_in_process_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_target_destroy (struct scsi_target*) ; 
 int /*<<< orphan*/  scsi_target_reap_usercontext ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void scsi_target_reap(struct scsi_target *starget)
{
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	unsigned long flags;
	enum scsi_target_state state;
	int empty = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	state = starget->state;
	if (--starget->reap_ref == 0 && list_empty(&starget->devices)) {
		empty = 1;
		starget->state = STARGET_DEL;
	}
	spin_unlock_irqrestore(shost->host_lock, flags);

	if (!empty)
		return;

	BUG_ON(state == STARGET_DEL);
	if (state == STARGET_CREATED)
		scsi_target_destroy(starget);
	else
		execute_in_process_context(scsi_target_reap_usercontext,
					   &starget->ew);
}