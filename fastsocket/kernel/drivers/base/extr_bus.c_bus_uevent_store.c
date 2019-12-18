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
struct bus_type {TYPE_2__* p; } ;
typedef  size_t ssize_t ;
typedef  enum kobject_action { ____Placeholder_kobject_action } kobject_action ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ subsys; } ;

/* Variables and functions */
 scalar_t__ kobject_action_type (char const*,size_t,int*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t bus_uevent_store(struct bus_type *bus,
				const char *buf, size_t count)
{
	enum kobject_action action;

	if (kobject_action_type(buf, count, &action) == 0)
		kobject_uevent(&bus->p->subsys.kobj, action);
	return count;
}