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
struct net_device {int if_port; int /*<<< orphan*/  flags; } ;
struct ifmap {int port; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFF_AUTOMEDIA ; 
#define  IF_PORT_10BASE2 129 
#define  IF_PORT_10BASET 128 
 int /*<<< orphan*/  etherh_setif (struct net_device*) ; 

__attribute__((used)) static int etherh_set_config(struct net_device *dev, struct ifmap *map)
{
	switch (map->port) {
	case IF_PORT_10BASE2:
	case IF_PORT_10BASET:
		/*
		 * If the user explicitly sets the interface
		 * media type, turn off automedia detection.
		 */
		dev->flags &= ~IFF_AUTOMEDIA;
		dev->if_port = map->port;
		break;

	default:
		return -EINVAL;
	}

	etherh_setif(dev);

	return 0;
}