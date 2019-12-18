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
struct Scsi_Host {scalar_t__ host_busy; scalar_t__ host_failed; int /*<<< orphan*/  ehandler; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_LOG_ERROR_RECOVERY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  trace_scsi_eh_wakeup (struct Scsi_Host*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void scsi_eh_wakeup(struct Scsi_Host *shost)
{
	if (shost->host_busy == shost->host_failed) {
		trace_scsi_eh_wakeup(shost);
		wake_up_process(shost->ehandler);
		SCSI_LOG_ERROR_RECOVERY(5,
				printk("Waking error handler thread\n"));
	}
}