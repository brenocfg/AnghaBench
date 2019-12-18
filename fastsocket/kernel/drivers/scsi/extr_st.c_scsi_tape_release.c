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
struct scsi_tape {struct scsi_tape* buffer; struct scsi_tape* reserved_pages; int /*<<< orphan*/ * device; struct gendisk* disk; } ;
struct kref {int dummy; } ;
struct gendisk {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct scsi_tape*) ; 
 int /*<<< orphan*/  normalize_buffer (struct scsi_tape*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 struct scsi_tape* to_scsi_tape (struct kref*) ; 

__attribute__((used)) static void scsi_tape_release(struct kref *kref)
{
	struct scsi_tape *tpnt = to_scsi_tape(kref);
	struct gendisk *disk = tpnt->disk;

	tpnt->device = NULL;

	if (tpnt->buffer) {
		normalize_buffer(tpnt->buffer);
		kfree(tpnt->buffer->reserved_pages);
		kfree(tpnt->buffer);
	}

	disk->private_data = NULL;
	put_disk(disk);
	kfree(tpnt);
	return;
}