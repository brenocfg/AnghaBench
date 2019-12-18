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
struct sockaddr {char* sa_data; } ;
struct net_device {int dummy; } ;
struct enic {int dummy; } ;

/* Variables and functions */
 int enic_dev_add_station_addr (struct enic*) ; 
 int enic_dev_del_station_addr (struct enic*) ; 
 int enic_set_mac_addr (struct net_device*,char*) ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enic_set_mac_address(struct net_device *netdev, void *p)
{
	struct sockaddr *saddr = p;
	char *addr = saddr->sa_data;
	struct enic *enic = netdev_priv(netdev);
	int err;

	err = enic_dev_del_station_addr(enic);
	if (err)
		return err;

	err = enic_set_mac_addr(netdev, addr);
	if (err)
		return err;

	return enic_dev_add_station_addr(enic);
}