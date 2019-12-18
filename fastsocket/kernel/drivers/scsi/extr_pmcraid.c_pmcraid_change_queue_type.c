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
struct scsi_device {int /*<<< orphan*/  queue_depth; scalar_t__ tagged_supported; scalar_t__ hostdata; } ;
struct pmcraid_resource_entry {int /*<<< orphan*/  cfg_entry; } ;

/* Variables and functions */
 scalar_t__ RES_IS_GSCSI (int /*<<< orphan*/ ) ; 
 scalar_t__ RES_IS_VSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_deactivate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_set_tag_type (struct scsi_device*,int) ; 

__attribute__((used)) static int pmcraid_change_queue_type(struct scsi_device *scsi_dev, int tag)
{
	struct pmcraid_resource_entry *res;

	res = (struct pmcraid_resource_entry *)scsi_dev->hostdata;

	if ((res) && scsi_dev->tagged_supported &&
	    (RES_IS_GSCSI(res->cfg_entry) || RES_IS_VSET(res->cfg_entry))) {
		scsi_set_tag_type(scsi_dev, tag);

		if (tag)
			scsi_activate_tcq(scsi_dev, scsi_dev->queue_depth);
		else
			scsi_deactivate_tcq(scsi_dev, scsi_dev->queue_depth);
	} else
		tag = 0;

	return tag;
}