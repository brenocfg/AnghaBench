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
struct scsi_cmnd {TYPE_1__* device; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int sleeptime ; 

int arcmsr_sleep_for_bus_reset(struct scsi_cmnd *cmd)
{
		struct Scsi_Host *shost = NULL;
		int i, isleep;
		shost = cmd->device->host;
		isleep = sleeptime / 10;
		if (isleep > 0) {
			for (i = 0; i < isleep; i++) {
				msleep(10000);
			}
		}

		isleep = sleeptime % 10;
		if (isleep > 0) {
			msleep(isleep*1000);
		}
		return 0;
}