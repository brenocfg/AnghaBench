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
struct net_device {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE802_TR ; 
 int /*<<< orphan*/  ip_eth_mc_map (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ip_tr_mc_map (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void qeth_l3_get_mac_for_ipm(__u32 ipm, char *mac,
				struct net_device *dev)
{
	if (dev->type == ARPHRD_IEEE802_TR)
		ip_tr_mc_map(ipm, mac);
	else
		ip_eth_mc_map(ipm, mac);
}