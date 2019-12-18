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
struct slave {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bonding {int /*<<< orphan*/  curr_slave_lock; struct slave* curr_active_slave; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct bonding* to_bond (struct device*) ; 

__attribute__((used)) static ssize_t bonding_show_mii_status(struct device *d,
				       struct device_attribute *attr,
				       char *buf)
{
	struct slave *curr;
	struct bonding *bond = to_bond(d);

	read_lock(&bond->curr_slave_lock);
	curr = bond->curr_active_slave;
	read_unlock(&bond->curr_slave_lock);

	return sprintf(buf, "%s\n", curr ? "up" : "down");
}