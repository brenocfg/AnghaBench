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
struct net_device {int dummy; } ;
struct fc_lport {int dummy; } ;

/* Variables and functions */
 struct net_device* fcoe_netdev (struct fc_lport*) ; 
 scalar_t__ netif_oper_up (struct net_device*) ; 

__attribute__((used)) static int fcoe_link_ok(struct fc_lport *lport)
{
	struct net_device *netdev = fcoe_netdev(lport);

	if (netif_oper_up(netdev))
		return 0;
	return -1;
}