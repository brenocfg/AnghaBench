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
struct net_bridge {int /*<<< orphan*/  hello_timer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_timer_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct net_bridge* to_bridge (struct device*) ; 

__attribute__((used)) static ssize_t show_hello_timer(struct device *d,
				struct device_attribute *attr, char *buf)
{
	struct net_bridge *br = to_bridge(d);
	return sprintf(buf, "%ld\n", br_timer_value(&br->hello_timer));
}