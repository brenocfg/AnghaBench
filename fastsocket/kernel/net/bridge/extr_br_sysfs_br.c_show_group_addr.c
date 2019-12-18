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
struct net_bridge {int* group_addr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int) ; 
 struct net_bridge* to_bridge (struct device*) ; 

__attribute__((used)) static ssize_t show_group_addr(struct device *d,
			       struct device_attribute *attr, char *buf)
{
	struct net_bridge *br = to_bridge(d);
	return sprintf(buf, "%x:%x:%x:%x:%x:%x\n",
		       br->group_addr[0], br->group_addr[1],
		       br->group_addr[2], br->group_addr[3],
		       br->group_addr[4], br->group_addr[5]);
}