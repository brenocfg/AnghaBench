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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_net_remove (struct net*,char*) ; 

__attribute__((used)) static void ipv6_proc_exit_net(struct net *net)
{
	proc_net_remove(net, "sockstat6");
	proc_net_remove(net, "dev_snmp6");
	proc_net_remove(net, "snmp6");
}