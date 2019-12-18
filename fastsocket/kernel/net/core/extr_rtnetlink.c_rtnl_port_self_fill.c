#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {int (* ndo_get_vf_port ) (struct net_device*,int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_PORT_SELF ; 
 int /*<<< orphan*/  PORT_SELF_VF ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int rtnl_port_self_fill(struct sk_buff *skb, struct net_device *dev)
{
	struct nlattr *port_self;
	int err;

	port_self = nla_nest_start(skb, IFLA_PORT_SELF);
	if (!port_self)
		return -EMSGSIZE;

	err = dev->netdev_ops->ndo_get_vf_port(dev, PORT_SELF_VF, skb);
	if (err) {
		nla_nest_cancel(skb, port_self);
		return (err == -EMSGSIZE) ? err : 0;
	}

	nla_nest_end(skb, port_self);

	return 0;
}