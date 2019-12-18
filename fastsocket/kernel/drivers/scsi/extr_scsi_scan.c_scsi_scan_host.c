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
struct async_scan_data {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_schedule (int /*<<< orphan*/ ,struct async_scan_data*) ; 
 int /*<<< orphan*/  do_scan_async ; 
 int /*<<< orphan*/  do_scsi_scan_host (struct Scsi_Host*) ; 
 struct async_scan_data* scsi_prep_async_scan (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_type ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void scsi_scan_host(struct Scsi_Host *shost)
{
	struct async_scan_data *data;

	if (strncmp(scsi_scan_type, "none", 4) == 0)
		return;

	data = scsi_prep_async_scan(shost);
	if (!data) {
		do_scsi_scan_host(shost);
		return;
	}

	/* register with the async subsystem so wait_for_device_probe()
	 * will flush this work
	 */
	async_schedule(do_scan_async, data);

	/* scsi_autopm_put_host(shost) is called in scsi_finish_async_scan() */
}