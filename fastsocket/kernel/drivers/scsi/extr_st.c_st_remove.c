#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_tape {int /*<<< orphan*/  kref; TYPE_2__* modes; struct scsi_device* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct scsi_device {TYPE_1__ sdev_gendev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** cdevs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_TAPE_MAJOR ; 
 int ST_NBR_MODES ; 
 int /*<<< orphan*/  TAPE_MINOR (int,int,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_tape_release ; 
 struct scsi_tape** scsi_tapes ; 
 int /*<<< orphan*/  st_dev_arr_lock ; 
 int st_dev_max ; 
 int /*<<< orphan*/  st_nr_dev ; 
 int /*<<< orphan*/  st_ref_mutex ; 
 int /*<<< orphan*/  st_sysfs_class ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_remove(struct device *dev)
{
	struct scsi_device *SDp = to_scsi_device(dev);
	struct scsi_tape *tpnt;
	int i, j, mode;

	write_lock(&st_dev_arr_lock);
	for (i = 0; i < st_dev_max; i++) {
		tpnt = scsi_tapes[i];
		if (tpnt != NULL && tpnt->device == SDp) {
			scsi_tapes[i] = NULL;
			st_nr_dev--;
			write_unlock(&st_dev_arr_lock);
			sysfs_remove_link(&tpnt->device->sdev_gendev.kobj,
					  "tape");
			for (mode = 0; mode < ST_NBR_MODES; ++mode) {
				for (j=0; j < 2; j++) {
					device_destroy(st_sysfs_class,
						       MKDEV(SCSI_TAPE_MAJOR,
							     TAPE_MINOR(i, mode, j)));
					cdev_del(tpnt->modes[mode].cdevs[j]);
					tpnt->modes[mode].cdevs[j] = NULL;
				}
			}

			mutex_lock(&st_ref_mutex);
			kref_put(&tpnt->kref, scsi_tape_release);
			mutex_unlock(&st_ref_mutex);
			return 0;
		}
	}

	write_unlock(&st_dev_arr_lock);
	return 0;
}