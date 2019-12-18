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
struct hpsa_scsi_dev_t {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; int /*<<< orphan*/  devtype; int /*<<< orphan*/  raid_level; } ;
struct ctlr_info {TYPE_2__* pdev; TYPE_1__** dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  raid_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HPSA_MAX_DEVICES ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_device_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpsa_scsi_update_entry(struct ctlr_info *h, int hostno,
	int entry, struct hpsa_scsi_dev_t *new_entry)
{
	/* assumes h->devlock is held */
	BUG_ON(entry < 0 || entry >= HPSA_MAX_DEVICES);

	/* Raid level changed. */
	h->dev[entry]->raid_level = new_entry->raid_level;
	dev_info(&h->pdev->dev, "%s device c%db%dt%dl%d updated.\n",
		scsi_device_type(new_entry->devtype), hostno, new_entry->bus,
		new_entry->target, new_entry->lun);
}