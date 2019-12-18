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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_ONLINE ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 TYPE_1__* to_ccwgroupdev (struct device*) ; 

__attribute__((used)) static ssize_t
ccwgroup_online_show (struct device *dev, struct device_attribute *attr, char *buf)
{
	int online;

	online = (to_ccwgroupdev(dev)->state == CCWGROUP_ONLINE);

	return sprintf(buf, online ? "1\n" : "0\n");
}