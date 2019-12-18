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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct can_ctrlmode {int /*<<< orphan*/  flags; } ;
struct can_priv {int state; int restart_ms; struct can_ctrlmode* bittiming_const; struct can_ctrlmode clock; struct can_ctrlmode bittiming; int /*<<< orphan*/  (* do_get_state ) (struct net_device const*,int*) ;int /*<<< orphan*/  ctrlmode; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;
typedef  int /*<<< orphan*/  cm ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_CAN_BITTIMING ; 
 int /*<<< orphan*/  IFLA_CAN_BITTIMING_CONST ; 
 int /*<<< orphan*/  IFLA_CAN_CLOCK ; 
 int /*<<< orphan*/  IFLA_CAN_CTRLMODE ; 
 int /*<<< orphan*/  IFLA_CAN_RESTART_MS ; 
 int /*<<< orphan*/  IFLA_CAN_STATE ; 
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct can_ctrlmode*) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct can_priv* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  stub1 (struct net_device const*,int*) ; 

__attribute__((used)) static int can_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);
	struct can_ctrlmode cm = {.flags = priv->ctrlmode};
	enum can_state state = priv->state;

	if (priv->do_get_state)
		priv->do_get_state(dev, &state);
	NLA_PUT_U32(skb, IFLA_CAN_STATE, state);
	NLA_PUT(skb, IFLA_CAN_CTRLMODE, sizeof(cm), &cm);
	NLA_PUT_U32(skb, IFLA_CAN_RESTART_MS, priv->restart_ms);
	NLA_PUT(skb, IFLA_CAN_BITTIMING,
		sizeof(priv->bittiming), &priv->bittiming);
	NLA_PUT(skb, IFLA_CAN_CLOCK, sizeof(cm), &priv->clock);
	if (priv->bittiming_const)
		NLA_PUT(skb, IFLA_CAN_BITTIMING_CONST,
			sizeof(*priv->bittiming_const), priv->bittiming_const);

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}