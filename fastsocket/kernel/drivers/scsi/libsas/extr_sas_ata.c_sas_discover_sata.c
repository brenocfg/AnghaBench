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
struct domain_device {scalar_t__ dev_type; int /*<<< orphan*/  port; int /*<<< orphan*/  rphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_PROBE ; 
 int ENODEV ; 
 scalar_t__ SATA_PM ; 
 int /*<<< orphan*/  sas_discover_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_fill_in_rphy (struct domain_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_get_ata_command_set (struct domain_device*) ; 
 int sas_notify_lldd_dev_found (struct domain_device*) ; 

int sas_discover_sata(struct domain_device *dev)
{
	int res;

	if (dev->dev_type == SATA_PM)
		return -ENODEV;

	sas_get_ata_command_set(dev);
	sas_fill_in_rphy(dev, dev->rphy);

	res = sas_notify_lldd_dev_found(dev);
	if (res)
		return res;

	sas_discover_event(dev->port, DISCE_PROBE);
	return 0;
}