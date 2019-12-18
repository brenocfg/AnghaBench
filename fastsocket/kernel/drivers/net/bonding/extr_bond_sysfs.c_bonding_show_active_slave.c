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
struct slave {TYPE_2__* dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct bonding {TYPE_1__ params; int /*<<< orphan*/  curr_slave_lock; struct slave* curr_active_slave; } ;
typedef  int ssize_t ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 scalar_t__ USES_PRIMARY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,char*) ; 
 struct bonding* to_bond (struct device*) ; 

__attribute__((used)) static ssize_t bonding_show_active_slave(struct device *d,
					 struct device_attribute *attr,
					 char *buf)
{
	struct slave *curr;
	struct bonding *bond = to_bond(d);
	int count = 0;

	read_lock(&bond->curr_slave_lock);
	curr = bond->curr_active_slave;
	read_unlock(&bond->curr_slave_lock);

	if (USES_PRIMARY(bond->params.mode) && curr)
		count = sprintf(buf, "%s\n", curr->dev->name);
	return count;
}