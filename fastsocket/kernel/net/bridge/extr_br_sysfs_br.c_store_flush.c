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
struct net_bridge {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 size_t EPERM ; 
 int /*<<< orphan*/  br_fdb_flush (struct net_bridge*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct net_bridge* to_bridge (struct device*) ; 

__attribute__((used)) static ssize_t store_flush(struct device *d,
			   struct device_attribute *attr,
			   const char *buf, size_t len)
{
	struct net_bridge *br = to_bridge(d);

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	br_fdb_flush(br);
	return len;
}