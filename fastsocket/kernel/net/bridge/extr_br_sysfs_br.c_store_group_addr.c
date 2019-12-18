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
typedef  int u8 ;
struct net_bridge {int* group_addr; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_link_local_ether_addr (int*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,int*,int*,int*,int*,int*,int*) ; 
 struct net_bridge* to_bridge (struct device*) ; 

__attribute__((used)) static ssize_t store_group_addr(struct device *d,
				struct device_attribute *attr,
				const char *buf, size_t len)
{
	struct net_bridge *br = to_bridge(d);
	u8 new_addr[6];
	int i;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (sscanf(buf, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		   &new_addr[0], &new_addr[1], &new_addr[2],
		   &new_addr[3], &new_addr[4], &new_addr[5]) != 6)
		return -EINVAL;

	if (!is_link_local_ether_addr(new_addr))
		return -EINVAL;

	if (new_addr[5] == 1 	/* 802.3x Pause address */
	    || new_addr[5] == 2 /* 802.3ad Slow protocols */
	    || new_addr[5] == 3) /* 802.1X PAE address */
		return -EINVAL;

	spin_lock_bh(&br->lock);
	for (i = 0; i < 6; i++)
		br->group_addr[i] = new_addr[i];
	spin_unlock_bh(&br->lock);
	return len;
}