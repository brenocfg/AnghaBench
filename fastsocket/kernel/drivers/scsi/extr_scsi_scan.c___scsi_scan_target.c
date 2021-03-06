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
struct scsi_target {int /*<<< orphan*/  dev; int /*<<< orphan*/  scsi_level; } ;
struct device {int dummy; } ;
struct Scsi_Host {unsigned int this_id; } ;

/* Variables and functions */
 unsigned int SCAN_WILD_CARD ; 
 int SCSI_SCAN_LUN_PRESENT ; 
 int SCSI_SCAN_TARGET_PRESENT ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct scsi_target* scsi_alloc_target (struct device*,unsigned int,unsigned int) ; 
 int scsi_probe_and_add_lun (struct scsi_target*,unsigned int,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_report_lun_scan (struct scsi_target*,int,int) ; 
 int /*<<< orphan*/  scsi_sequential_lun_scan (struct scsi_target*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_target_reap (struct scsi_target*) ; 

__attribute__((used)) static void __scsi_scan_target(struct device *parent, unsigned int channel,
		unsigned int id, unsigned int lun, int rescan)
{
	struct Scsi_Host *shost = dev_to_shost(parent);
	int bflags = 0;
	int res;
	struct scsi_target *starget;

	if (shost->this_id == id)
		/*
		 * Don't scan the host adapter
		 */
		return;

	starget = scsi_alloc_target(parent, channel, id);
	if (!starget)
		return;

	if (lun != SCAN_WILD_CARD) {
		/*
		 * Scan for a specific host/chan/id/lun.
		 */
		scsi_probe_and_add_lun(starget, lun, NULL, NULL, rescan, NULL);
		goto out_reap;
	}

	/*
	 * Scan LUN 0, if there is some response, scan further. Ideally, we
	 * would not configure LUN 0 until all LUNs are scanned.
	 */
	res = scsi_probe_and_add_lun(starget, 0, &bflags, NULL, rescan, NULL);
	if (res == SCSI_SCAN_LUN_PRESENT || res == SCSI_SCAN_TARGET_PRESENT) {
		if (scsi_report_lun_scan(starget, bflags, rescan) != 0)
			/*
			 * The REPORT LUN did not scan the target,
			 * do a sequential scan.
			 */
			scsi_sequential_lun_scan(starget, bflags,
						 starget->scsi_level, rescan);
	}

 out_reap:
	/* now determine if the target has any children at all
	 * and if not, nuke it */
	scsi_target_reap(starget);

	put_device(&starget->dev);
}