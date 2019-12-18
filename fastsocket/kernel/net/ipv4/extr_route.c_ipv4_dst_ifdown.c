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
struct rtable {struct in_device* idev; } ;
struct net_device {int dummy; } ;
struct in_device {struct net_device* dev; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {struct net_device* loopback_dev; } ;

/* Variables and functions */
 TYPE_1__* dev_net (struct net_device*) ; 
 struct in_device* in_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 

__attribute__((used)) static void ipv4_dst_ifdown(struct dst_entry *dst, struct net_device *dev,
			    int how)
{
	struct rtable *rt = (struct rtable *) dst;
	struct in_device *idev = rt->idev;
	if (dev != dev_net(dev)->loopback_dev && idev && idev->dev == dev) {
		struct in_device *loopback_idev =
			in_dev_get(dev_net(dev)->loopback_dev);
		if (loopback_idev) {
			rt->idev = loopback_idev;
			in_dev_put(idev);
		}
	}
}