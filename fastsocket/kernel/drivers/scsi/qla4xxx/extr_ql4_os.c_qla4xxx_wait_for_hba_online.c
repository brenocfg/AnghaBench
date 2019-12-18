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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 unsigned long HBA_ONLINE_TOV ; 
 unsigned long HZ ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ adapter_up (struct scsi_qla_host*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int qla4xxx_wait_for_hba_online(struct scsi_qla_host *ha)
{
	unsigned long wait_online;

	wait_online = jiffies + (HBA_ONLINE_TOV * HZ);
	while (time_before(jiffies, wait_online)) {

		if (adapter_up(ha))
			return QLA_SUCCESS;

		msleep(2000);
	}

	return QLA_ERROR;
}