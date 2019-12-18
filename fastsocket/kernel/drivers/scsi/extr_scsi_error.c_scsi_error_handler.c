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
struct Scsi_Host {scalar_t__ host_failed; scalar_t__ host_eh_scheduled; scalar_t__ host_busy; int /*<<< orphan*/ * ehandler; int /*<<< orphan*/  host_no; TYPE_1__* transportt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eh_strategy_handler ) (struct Scsi_Host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_LOG_ERROR_RECOVERY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  scsi_restart_operations (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_unjam_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct Scsi_Host*) ; 

int scsi_error_handler(void *data)
{
	struct Scsi_Host *shost = data;

	/*
	 * We use TASK_INTERRUPTIBLE so that the thread is not
	 * counted against the load average as a running process.
	 * We never actually get interrupted because kthread_run
	 * disables signal delivery for the created thread.
	 */
	while (!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);
		if ((shost->host_failed == 0 && shost->host_eh_scheduled == 0) ||
		    shost->host_failed != shost->host_busy) {
			SCSI_LOG_ERROR_RECOVERY(1,
				printk("scsi_eh_%d: sleeping\n",
					shost->host_no));
			schedule();
			continue;
		}

		__set_current_state(TASK_RUNNING);
		SCSI_LOG_ERROR_RECOVERY(1,
			printk("scsi_eh_%d: waking up %d/%d/%d\n",
			       shost->host_no, shost->host_eh_scheduled,
			       shost->host_failed, shost->host_busy));

		/*
		 * We have a host that is failing for some reason.  Figure out
		 * what we need to do to get it up and online again (if we can).
		 * If we fail, we end up taking the thing offline.
		 */
		if (shost->transportt->eh_strategy_handler)
			shost->transportt->eh_strategy_handler(shost);
		else
			scsi_unjam_host(shost);

		/*
		 * Note - if the above fails completely, the action is to take
		 * individual devices offline and flush the queue of any
		 * outstanding requests that may have been pending.  When we
		 * restart, we restart any I/O to any other devices on the bus
		 * which are still online.
		 */
		scsi_restart_operations(shost);
	}
	__set_current_state(TASK_RUNNING);

	SCSI_LOG_ERROR_RECOVERY(1,
		printk("Error handler scsi_eh_%d exiting\n", shost->host_no));
	shost->ehandler = NULL;
	return 0;
}