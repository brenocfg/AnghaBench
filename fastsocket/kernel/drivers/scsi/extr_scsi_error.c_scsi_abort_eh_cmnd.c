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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 scalar_t__ SUCCESS ; 
 scalar_t__ __scsi_try_to_abort_cmd (struct scsi_cmnd*) ; 
 scalar_t__ scsi_try_bus_device_reset (struct scsi_cmnd*) ; 
 scalar_t__ scsi_try_bus_reset (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_try_host_reset (struct scsi_cmnd*) ; 
 scalar_t__ scsi_try_target_reset (struct scsi_cmnd*) ; 

__attribute__((used)) static void scsi_abort_eh_cmnd(struct scsi_cmnd *scmd)
{
	if (__scsi_try_to_abort_cmd(scmd) != SUCCESS)
		if (scsi_try_bus_device_reset(scmd) != SUCCESS)
			if (scsi_try_target_reset(scmd) != SUCCESS)
				if (scsi_try_bus_reset(scmd) != SUCCESS)
					scsi_try_host_reset(scmd);
}