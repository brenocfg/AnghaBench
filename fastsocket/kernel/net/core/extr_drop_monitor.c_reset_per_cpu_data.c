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
struct per_cpu_dm_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  skb; int /*<<< orphan*/  send_timer; } ;
struct nlattr {int dummy; } ;
struct net_dm_drop_point {int dummy; } ;
struct net_dm_alert_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  NET_DM_CMD_ALERT ; 
 int /*<<< orphan*/  NLA_UNSPEC ; 
 int dm_hit_limit ; 
 struct sk_buff* genlmsg_new (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (struct net_dm_alert_msg*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  net_drop_monitor_family ; 
 struct net_dm_alert_msg* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *reset_per_cpu_data(struct per_cpu_dm_data *data)
{
	size_t al;
	struct net_dm_alert_msg *msg;
	struct nlattr *nla;
	struct sk_buff *skb;
	unsigned long flags;

	al = sizeof(struct net_dm_alert_msg);
	al += dm_hit_limit * sizeof(struct net_dm_drop_point);
	al += sizeof(struct nlattr);

	skb = genlmsg_new(al, GFP_KERNEL);

	if (skb) {
		genlmsg_put(skb, 0, 0, &net_drop_monitor_family,
				0, NET_DM_CMD_ALERT);
		nla = nla_reserve(skb, NLA_UNSPEC,
				  sizeof(struct net_dm_alert_msg));
		msg = nla_data(nla);
		memset(msg, 0, al);
	} else {
		mod_timer(&data->send_timer, jiffies + HZ / 10);
	}

	spin_lock_irqsave(&data->lock, flags);
	swap(data->skb, skb);
	spin_unlock_irqrestore(&data->lock, flags);

	return skb;
}