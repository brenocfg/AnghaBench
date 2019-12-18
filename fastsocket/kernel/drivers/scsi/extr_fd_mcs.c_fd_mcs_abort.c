#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  phase; } ;
struct TYPE_10__ {int result; TYPE_1__ SCp; } ;
struct TYPE_9__ {TYPE_2__* device; } ;
struct TYPE_8__ {struct Scsi_Host* host; } ;
typedef  TYPE_3__ Scsi_Cmnd ;

/* Variables and functions */
 int DID_ABORT ; 
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  aborted ; 
 TYPE_6__* current_SC ; 
 int /*<<< orphan*/  fd_mcs_make_bus_idle (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fd_mcs_print_info (TYPE_3__*) ; 
 int /*<<< orphan*/  in_command ; 
 int /*<<< orphan*/  my_done (struct Scsi_Host*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int fd_mcs_abort(Scsi_Cmnd * SCpnt)
{
	struct Scsi_Host *shpnt = SCpnt->device->host;

	unsigned long flags;
#if EVERY_ACCESS || ERRORS_ONLY || DEBUG_ABORT
	printk("fd_mcs: abort ");
#endif

	spin_lock_irqsave(shpnt->host_lock, flags);
	if (!in_command) {
#if EVERY_ACCESS || ERRORS_ONLY
		printk(" (not in command)\n");
#endif
		spin_unlock_irqrestore(shpnt->host_lock, flags);
		return FAILED;
	} else
		printk("\n");

#if DEBUG_ABORT
	fd_mcs_print_info(SCpnt);
#endif

	fd_mcs_make_bus_idle(shpnt);

	current_SC->SCp.phase |= aborted;

	current_SC->result = DID_ABORT << 16;

	/* Aborts are not done well. . . */
	my_done(shpnt, DID_ABORT << 16);

	spin_unlock_irqrestore(shpnt->host_lock, flags);
	return SUCCESS;
}