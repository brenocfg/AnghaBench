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
struct serio_driver {int manual_bind; } ;
struct device_driver {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 
 struct serio_driver* to_serio_driver (struct device_driver*) ; 

__attribute__((used)) static ssize_t serio_driver_set_bind_mode(struct device_driver *drv, const char *buf, size_t count)
{
	struct serio_driver *serio_drv = to_serio_driver(drv);
	int retval;

	retval = count;
	if (!strncmp(buf, "manual", count)) {
		serio_drv->manual_bind = true;
	} else if (!strncmp(buf, "auto", count)) {
		serio_drv->manual_bind = false;
	} else {
		retval = -EINVAL;
	}

	return retval;
}