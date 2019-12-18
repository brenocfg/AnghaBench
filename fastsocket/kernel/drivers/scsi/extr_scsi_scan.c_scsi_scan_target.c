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
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  scan_mutex; int /*<<< orphan*/  async_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  __scsi_scan_target (struct device*,unsigned int,unsigned int,unsigned int,int) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_complete_async_scans () ; 
 scalar_t__ scsi_host_scan_allowed (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_type ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void scsi_scan_target(struct device *parent, unsigned int channel,
		      unsigned int id, unsigned int lun, int rescan)
{
	struct Scsi_Host *shost = dev_to_shost(parent);

	if (strncmp(scsi_scan_type, "none", 4) == 0)
		return;

	mutex_lock(&shost->scan_mutex);
	if (!shost->async_scan)
		scsi_complete_async_scans();

	if (scsi_host_scan_allowed(shost))
		__scsi_scan_target(parent, channel, id, lun, rescan);
	mutex_unlock(&shost->scan_mutex);
}