#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* ops; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int (* bind ) (struct socket*,struct sockaddr*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENODEV ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 struct net_device* __dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ inet_select_addr (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct socket*,struct sockaddr*,int) ; 

__attribute__((used)) static int bind_mcastif_addr(struct socket *sock, char *ifname)
{
	struct net_device *dev;
	__be32 addr;
	struct sockaddr_in sin;

	if ((dev = __dev_get_by_name(&init_net, ifname)) == NULL)
		return -ENODEV;

	addr = inet_select_addr(dev, 0, RT_SCOPE_UNIVERSE);
	if (!addr)
		pr_err("You probably need to specify IP address on "
		       "multicast interface.\n");

	IP_VS_DBG(7, "binding socket with (%s) %pI4\n",
		  ifname, &addr);

	/* Now bind the socket with the address of multicast interface */
	sin.sin_family	     = AF_INET;
	sin.sin_addr.s_addr  = addr;
	sin.sin_port         = 0;

	return sock->ops->bind(sock, (struct sockaddr*)&sin, sizeof(sin));
}