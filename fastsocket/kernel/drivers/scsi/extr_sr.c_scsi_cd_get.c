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
struct scsi_cd {int /*<<< orphan*/  kref; int /*<<< orphan*/  device; } ;
struct gendisk {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct scsi_cd* scsi_cd (struct gendisk*) ; 
 scalar_t__ scsi_device_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_kref_release ; 
 int /*<<< orphan*/  sr_ref_mutex ; 

__attribute__((used)) static inline struct scsi_cd *scsi_cd_get(struct gendisk *disk)
{
	struct scsi_cd *cd = NULL;

	mutex_lock(&sr_ref_mutex);
	if (disk->private_data == NULL)
		goto out;
	cd = scsi_cd(disk);
	kref_get(&cd->kref);
	if (scsi_device_get(cd->device))
		goto out_put;
	goto out;

 out_put:
	kref_put(&cd->kref, sr_kref_release);
	cd = NULL;
 out:
	mutex_unlock(&sr_ref_mutex);
	return cd;
}