#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct pmcraid_instance {TYPE_1__ cdev; TYPE_2__* pdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_8__ {int id; } ;
struct TYPE_7__ {int number; } ;
struct TYPE_6__ {int devfn; TYPE_3__* bus; } ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 TYPE_4__ pmcraid_event_family ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static ssize_t pmcraid_show_adapter_id(
	struct device *dev,
	struct device_attribute *attr,
	char *buf
)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct pmcraid_instance *pinstance =
		(struct pmcraid_instance *)shost->hostdata;
	u32 adapter_id = (pinstance->pdev->bus->number << 8) |
		pinstance->pdev->devfn;
	u32 aen_group = pmcraid_event_family.id;

	return snprintf(buf, PAGE_SIZE,
			"adapter id: %d\nminor: %d\naen group: %d\n",
			adapter_id, MINOR(pinstance->cdev.dev), aen_group);
}