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
struct kobject {int dummy; } ;
struct bus_type_private {int /*<<< orphan*/  bus; } ;
struct bus_attribute {int /*<<< orphan*/  (* show ) (int /*<<< orphan*/ ,char*) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 struct bus_type_private* to_bus (struct kobject*) ; 
 struct bus_attribute* to_bus_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t bus_attr_show(struct kobject *kobj, struct attribute *attr,
			     char *buf)
{
	struct bus_attribute *bus_attr = to_bus_attr(attr);
	struct bus_type_private *bus_priv = to_bus(kobj);
	ssize_t ret = 0;

	if (bus_attr->show)
		ret = bus_attr->show(bus_priv->bus, buf);
	return ret;
}