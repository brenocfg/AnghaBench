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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct ip_tunnel_parm {int dummy; } ;

/* Variables and functions */
 int ip_tunnel_newlink (struct net_device*,struct nlattr**,struct ip_tunnel_parm*) ; 
 int /*<<< orphan*/  ipgre_netlink_parms (struct nlattr**,struct nlattr**,struct ip_tunnel_parm*) ; 

__attribute__((used)) static int ipgre_newlink(struct net_device *dev,
			 struct nlattr *tb[], struct nlattr *data[])
{
	struct ip_tunnel_parm p;

	ipgre_netlink_parms(data, tb, &p);
	return ip_tunnel_newlink(dev, tb, &p);
}