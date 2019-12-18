#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct langwell_udc {TYPE_1__* driver; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 struct langwell_udc* the_controller ; 

__attribute__((used)) static ssize_t show_function(struct device *_dev,
		struct device_attribute *attr, char *buf)
{
	struct langwell_udc	*dev = the_controller;

	if (!dev->driver || !dev->driver->function
			|| strlen(dev->driver->function) > PAGE_SIZE)
		return 0;

	return scnprintf(buf, PAGE_SIZE, "%s\n", dev->driver->function);
}