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
struct domain_device {scalar_t__ lldd_dev; TYPE_2__* port; } ;
struct TYPE_4__ {TYPE_1__* ha; } ;
struct TYPE_3__ {int /*<<< orphan*/  lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  asd_free_ddb (int /*<<< orphan*/ ,int) ; 
 int asd_init_sata_pm_table_ddb (struct domain_device*) ; 
 int asd_init_target_ddb (struct domain_device*) ; 

__attribute__((used)) static int asd_init_sata_pm_ddb(struct domain_device *dev)
{
	int res = 0;

	res = asd_init_target_ddb(dev);
	if (res)
		goto out;
	res = asd_init_sata_pm_table_ddb(dev);
	if (res)
		asd_free_ddb(dev->port->ha->lldd_ha,
			     (int) (unsigned long) dev->lldd_dev);
out:
	return res;
}