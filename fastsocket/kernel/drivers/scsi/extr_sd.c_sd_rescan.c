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
struct scsi_disk {int /*<<< orphan*/  disk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  revalidate_disk (int /*<<< orphan*/ ) ; 
 struct scsi_disk* scsi_disk_get_from_dev (struct device*) ; 
 int /*<<< orphan*/  scsi_disk_put (struct scsi_disk*) ; 

__attribute__((used)) static void sd_rescan(struct device *dev)
{
	struct scsi_disk *sdkp = scsi_disk_get_from_dev(dev);

	if (sdkp) {
		revalidate_disk(sdkp->disk);
		scsi_disk_put(sdkp);
	}
}