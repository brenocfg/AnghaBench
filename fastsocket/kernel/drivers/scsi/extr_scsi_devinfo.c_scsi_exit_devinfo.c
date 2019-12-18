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

/* Variables and functions */
 int /*<<< orphan*/  SCSI_DEVINFO_GLOBAL ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dev_info_remove_list (int /*<<< orphan*/ ) ; 

void scsi_exit_devinfo(void)
{
#ifdef CONFIG_SCSI_PROC_FS
	remove_proc_entry("scsi/device_info", NULL);
#endif

	scsi_dev_info_remove_list(SCSI_DEVINFO_GLOBAL);
}