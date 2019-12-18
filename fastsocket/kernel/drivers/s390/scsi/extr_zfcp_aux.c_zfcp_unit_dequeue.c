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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct zfcp_unit {TYPE_2__ sysfs_device; int /*<<< orphan*/  port; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; int /*<<< orphan*/  remove_wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  config_lock; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_port_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_sysfs_unit_attrs ; 

void zfcp_unit_dequeue(struct zfcp_unit *unit)
{
	wait_event(unit->remove_wq, atomic_read(&unit->refcount) == 0);
	write_lock_irq(&zfcp_data.config_lock);
	list_del(&unit->list);
	write_unlock_irq(&zfcp_data.config_lock);
	zfcp_port_put(unit->port);
	sysfs_remove_group(&unit->sysfs_device.kobj, &zfcp_sysfs_unit_attrs);
	device_unregister(&unit->sysfs_device);
}