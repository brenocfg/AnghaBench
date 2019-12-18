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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bonding {TYPE_2__* primary_slave; } ;
typedef  int ssize_t ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int sprintf (char*,char*,char*) ; 
 struct bonding* to_bond (struct device*) ; 

__attribute__((used)) static ssize_t bonding_show_primary(struct device *d,
				    struct device_attribute *attr,
				    char *buf)
{
	int count = 0;
	struct bonding *bond = to_bond(d);

	if (bond->primary_slave)
		count = sprintf(buf, "%s\n", bond->primary_slave->dev->name);

	return count;
}