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

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MIBII_POLL_TICKS ; 
 int /*<<< orphan*/ * fd_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* ifmib_reg ; 
 void* ipForward_reg ; 
 void* ipmib_reg ; 
 int /*<<< orphan*/  mibII_poll_ticks ; 
 int /*<<< orphan*/ * mibII_poll_timer ; 
 int /*<<< orphan*/  mib_arp_update () ; 
 int /*<<< orphan*/  mib_fetch_route () ; 
 scalar_t__ mib_ifstack_last_change ; 
 scalar_t__ mib_iftable_last_change ; 
 int /*<<< orphan*/  mib_refresh_iflist () ; 
 int /*<<< orphan*/  mibif_restart_mibII_poll_timer () ; 
 int /*<<< orphan*/  module ; 
 int /*<<< orphan*/  oid_ifMIB ; 
 int /*<<< orphan*/  oid_ipForward ; 
 int /*<<< orphan*/  oid_ipMIB ; 
 int /*<<< orphan*/  oid_tcpMIB ; 
 int /*<<< orphan*/  oid_udpMIB ; 
 void* or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route ; 
 int /*<<< orphan*/ * route_fd ; 
 int /*<<< orphan*/  route_input ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 void* tcpmib_reg ; 
 void* udpmib_reg ; 
 int /*<<< orphan*/  update_ifa_info () ; 

__attribute__((used)) static void
mibII_start(void)
{
	if ((route_fd = fd_select(route, route_input, NULL, module)) == NULL) {
		syslog(LOG_ERR, "fd_select(route): %m");
		return;
	}
	mib_refresh_iflist();
	update_ifa_info();
	mib_arp_update();
	(void)mib_fetch_route();
	mib_iftable_last_change = 0;
	mib_ifstack_last_change = 0;

	ifmib_reg = or_register(&oid_ifMIB,
	    "The MIB module to describe generic objects for network interface"
	    " sub-layers.", module);

	ipmib_reg = or_register(&oid_ipMIB,
	   "The MIB module for managing IP and ICMP implementations, but "
	   "excluding their management of IP routes.", module);

	tcpmib_reg = or_register(&oid_tcpMIB,
	   "The MIB module for managing TCP implementations.", module);

	udpmib_reg = or_register(&oid_udpMIB,
	   "The MIB module for managing UDP implementations.", module);

	ipForward_reg = or_register(&oid_ipForward,
	   "The MIB module for the display of CIDR multipath IP Routes.",
	   module);

	mibII_poll_timer = NULL;
	mibII_poll_ticks = MIBII_POLL_TICKS;
	mibif_restart_mibII_poll_timer();
}