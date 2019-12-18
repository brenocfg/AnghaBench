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
struct TYPE_4__ {int /*<<< orphan*/  remote; int /*<<< orphan*/  sid; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__ pppoe; } ;
struct sockaddr_pppox {TYPE_1__ sa_addr; } ;
struct pppox_sock {int dummy; } ;
struct pppoe_net {int dummy; } ;
struct net_device {int ifindex; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_by_name (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct pppox_sock* get_item (struct pppoe_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pppoe_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pppoe_net_id ; 

__attribute__((used)) static inline struct pppox_sock *get_item_by_addr(struct net *net,
						struct sockaddr_pppox *sp)
{
	struct net_device *dev;
	struct pppoe_net *pn;
	struct pppox_sock *pppox_sock;

	int ifindex;

	dev = dev_get_by_name(net, sp->sa_addr.pppoe.dev);
	if (!dev)
		return NULL;

	ifindex = dev->ifindex;
	pn = net_generic(net, pppoe_net_id);
	pppox_sock = get_item(pn, sp->sa_addr.pppoe.sid,
				sp->sa_addr.pppoe.remote, ifindex);
	dev_put(dev);

	return pppox_sock;
}