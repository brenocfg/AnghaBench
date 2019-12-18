#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cd {int /*<<< orphan*/  kref; int /*<<< orphan*/  disk; TYPE_1__* device; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_prep_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 struct scsi_cd* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_prep_fn ; 
 int /*<<< orphan*/  sr_kref_release ; 
 int /*<<< orphan*/  sr_ref_mutex ; 

__attribute__((used)) static int sr_remove(struct device *dev)
{
	struct scsi_cd *cd = dev_get_drvdata(dev);

	blk_queue_prep_rq(cd->device->request_queue, scsi_prep_fn);
	del_gendisk(cd->disk);

	mutex_lock(&sr_ref_mutex);
	kref_put(&cd->kref, sr_kref_release);
	mutex_unlock(&sr_ref_mutex);

	return 0;
}