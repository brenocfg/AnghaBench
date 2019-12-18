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
struct scsi_device {int /*<<< orphan*/ * hostdata; } ;
struct pmcraid_resource_entry {int /*<<< orphan*/ * scsi_dev; } ;

/* Variables and functions */

__attribute__((used)) static void pmcraid_slave_destroy(struct scsi_device *scsi_dev)
{
	struct pmcraid_resource_entry *res;

	res = (struct pmcraid_resource_entry *)scsi_dev->hostdata;

	if (res)
		res->scsi_dev = NULL;

	scsi_dev->hostdata = NULL;
}