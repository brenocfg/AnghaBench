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
struct net_device {unsigned int flags; unsigned int gflags; } ;

/* Variables and functions */
 unsigned int IFF_ALLMULTI ; 
 unsigned int IFF_PROMISC ; 

__attribute__((used)) static unsigned int rtnl_dev_get_flags(const struct net_device *dev)
{
	return (dev->flags & ~(IFF_PROMISC | IFF_ALLMULTI)) |
	       (dev->gflags & (IFF_PROMISC | IFF_ALLMULTI));
}