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
struct domain_device {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_PROBE ; 
 int /*<<< orphan*/  sas_discover_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sas_notify_lldd_dev_found (struct domain_device*) ; 

int sas_discover_end_dev(struct domain_device *dev)
{
	int res;

	res = sas_notify_lldd_dev_found(dev);
	if (res)
		return res;
	sas_discover_event(dev->port, DISCE_PROBE);

	return 0;
}