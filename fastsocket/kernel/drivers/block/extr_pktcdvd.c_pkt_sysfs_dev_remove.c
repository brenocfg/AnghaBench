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
struct pktcdvd_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  kobj_wqueue; int /*<<< orphan*/  kobj_stat; } ;

/* Variables and functions */
 scalar_t__ class_pktcdvd ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_kobj_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pkt_sysfs_dev_remove(struct pktcdvd_device *pd)
{
	pkt_kobj_remove(pd->kobj_stat);
	pkt_kobj_remove(pd->kobj_wqueue);
	if (class_pktcdvd)
		device_unregister(pd->dev);
}