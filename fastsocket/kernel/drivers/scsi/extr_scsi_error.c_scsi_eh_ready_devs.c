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
struct list_head {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_eh_bus_device_reset (struct Scsi_Host*,struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  scsi_eh_bus_reset (struct Scsi_Host*,struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  scsi_eh_host_reset (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  scsi_eh_offline_sdevs (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  scsi_eh_stu (struct Scsi_Host*,struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  scsi_eh_target_reset (struct Scsi_Host*,struct list_head*,struct list_head*) ; 

void scsi_eh_ready_devs(struct Scsi_Host *shost,
			struct list_head *work_q,
			struct list_head *done_q)
{
	if (!scsi_eh_stu(shost, work_q, done_q))
		if (!scsi_eh_bus_device_reset(shost, work_q, done_q))
			if (!scsi_eh_target_reset(shost, work_q, done_q))
				if (!scsi_eh_bus_reset(shost, work_q, done_q))
					if (!scsi_eh_host_reset(work_q, done_q))
						scsi_eh_offline_sdevs(work_q,
								      done_q);
}