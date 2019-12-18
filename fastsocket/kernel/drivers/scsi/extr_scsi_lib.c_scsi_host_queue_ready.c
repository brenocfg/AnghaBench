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
struct scsi_device {int /*<<< orphan*/  starved_entry; } ;
struct request_queue {int dummy; } ;
struct Scsi_Host {scalar_t__ host_busy; scalar_t__ host_blocked; int /*<<< orphan*/  starved_list; int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_LOG_MLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_host_in_recovery (struct Scsi_Host*) ; 
 scalar_t__ scsi_host_is_busy (struct Scsi_Host*) ; 

__attribute__((used)) static inline int scsi_host_queue_ready(struct request_queue *q,
				   struct Scsi_Host *shost,
				   struct scsi_device *sdev)
{
	if (scsi_host_in_recovery(shost))
		return 0;
	if (shost->host_busy == 0 && shost->host_blocked) {
		/*
		 * unblock after host_blocked iterates to zero
		 */
		if (--shost->host_blocked == 0) {
			SCSI_LOG_MLQUEUE(3,
				printk("scsi%d unblocking host at zero depth\n",
					shost->host_no));
		} else {
			return 0;
		}
	}
	if (scsi_host_is_busy(shost)) {
		if (list_empty(&sdev->starved_entry))
			list_add_tail(&sdev->starved_entry, &shost->starved_list);
		return 0;
	}

	/* We're OK to process the command, so we can't be starved */
	if (!list_empty(&sdev->starved_entry))
		list_del_init(&sdev->starved_entry);

	return 1;
}