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
struct serio_driver {char* description; } ;
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct serio_driver* to_serio_driver (struct device_driver*) ; 

__attribute__((used)) static ssize_t serio_driver_show_description(struct device_driver *drv, char *buf)
{
	struct serio_driver *driver = to_serio_driver(drv);
	return sprintf(buf, "%s\n", driver->description ? driver->description : "(none)");
}