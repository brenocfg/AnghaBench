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
struct kset {int dummy; } ;
struct kobject {int dummy; } ;
struct device {TYPE_2__* class; TYPE_1__* bus; } ;
struct TYPE_4__ {char const* name; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 struct device* to_dev (struct kobject*) ; 

__attribute__((used)) static const char *dev_uevent_name(struct kset *kset, struct kobject *kobj)
{
	struct device *dev = to_dev(kobj);

	if (dev->bus)
		return dev->bus->name;
	if (dev->class)
		return dev->class->name;
	return NULL;
}