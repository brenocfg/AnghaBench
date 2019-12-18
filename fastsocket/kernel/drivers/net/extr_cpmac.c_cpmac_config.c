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
struct net_device {int flags; scalar_t__ base_addr; } ;
struct ifmap {scalar_t__ base_addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int IFF_UP ; 

__attribute__((used)) static int cpmac_config(struct net_device *dev, struct ifmap *map)
{
	if (dev->flags & IFF_UP)
		return -EBUSY;

	/* Don't allow changing the I/O address */
	if (map->base_addr != dev->base_addr)
		return -EOPNOTSUPP;

	/* ignore other fields */
	return 0;
}