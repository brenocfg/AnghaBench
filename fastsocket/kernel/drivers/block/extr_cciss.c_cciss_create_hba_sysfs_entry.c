#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; } ;
struct ctlr_info {TYPE_2__ dev; TYPE_1__* pdev; int /*<<< orphan*/  devname; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cciss_bus_type ; 
 int /*<<< orphan*/  cciss_host_type ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 

__attribute__((used)) static int cciss_create_hba_sysfs_entry(struct ctlr_info *h)
{
	device_initialize(&h->dev);
	h->dev.type = &cciss_host_type;
	h->dev.bus = &cciss_bus_type;
	dev_set_name(&h->dev, "%s", h->devname);
	h->dev.parent = &h->pdev->dev;

	return device_add(&h->dev);
}