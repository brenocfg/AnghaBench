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
struct scsi_device {scalar_t__ type; } ;
struct osst_tape {struct osst_tape* buffer; int /*<<< orphan*/  header_cache; int /*<<< orphan*/  drive; struct scsi_device* device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSST_MAJOR ; 
 scalar_t__ TYPE_TAPE ; 
 int /*<<< orphan*/  kfree (struct osst_tape*) ; 
 int /*<<< orphan*/  normalize_buffer (struct osst_tape*) ; 
 struct osst_tape** os_scsi_tapes ; 
 int /*<<< orphan*/  os_scsi_tapes_lock ; 
 int osst_max_dev ; 
 scalar_t__ osst_nr_dev ; 
 int /*<<< orphan*/  osst_sysfs_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int osst_remove(struct device *dev)
{
	struct scsi_device * SDp = to_scsi_device(dev);
	struct osst_tape * tpnt;
	int i;

	if ((SDp->type != TYPE_TAPE) || (osst_nr_dev <= 0))
		return 0;

	write_lock(&os_scsi_tapes_lock);
	for(i=0; i < osst_max_dev; i++) {
		if((tpnt = os_scsi_tapes[i]) && (tpnt->device == SDp)) {
			osst_sysfs_destroy(MKDEV(OSST_MAJOR, i));
			osst_sysfs_destroy(MKDEV(OSST_MAJOR, i+128));
			tpnt->device = NULL;
			put_disk(tpnt->drive);
			os_scsi_tapes[i] = NULL;
			osst_nr_dev--;
			write_unlock(&os_scsi_tapes_lock);
			vfree(tpnt->header_cache);
			if (tpnt->buffer) {
				normalize_buffer(tpnt->buffer);
				kfree(tpnt->buffer);
			}
			kfree(tpnt);
			return 0;
		}
	}
	write_unlock(&os_scsi_tapes_lock);
	return 0;
}