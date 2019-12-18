#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; } ;
struct TYPE_4__ {int /*<<< orphan*/  expires; } ;
struct net_bridge_port_group {TYPE_1__ timer; struct net_bridge_port_group* next; } ;
struct net_bridge_port {scalar_t__ state; } ;
struct net_bridge_mdb_entry {int timer_armed; struct net_bridge_port_group* ports; TYPE_1__ timer; scalar_t__ mglist; } ;
struct net_bridge {unsigned long multicast_membership_interval; unsigned long multicast_last_member_count; int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  mdb; int /*<<< orphan*/  dev; } ;
struct iphdr {int /*<<< orphan*/  saddr; } ;
struct igmpv3_query {scalar_t__ code; scalar_t__ nsrcs; } ;
struct igmphdr {int code; scalar_t__ group; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ BR_STATE_DISABLED ; 
 int EINVAL ; 
 int HZ ; 
 int IGMPV3_MRC (scalar_t__) ; 
 int IGMP_TIMER_SCALE ; 
 struct net_bridge_mdb_entry* br_mdb_ip4_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  br_multicast_query_received (struct net_bridge*,struct net_bridge_port*,int) ; 
 struct igmphdr* igmp_hdr (struct sk_buff*) ; 
 struct igmpv3_query* igmpv3_query_hdr (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int time_after (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 
 scalar_t__ try_to_del_timer_sync (TYPE_1__*) ; 

__attribute__((used)) static int br_ip4_multicast_query(struct net_bridge *br,
				  struct net_bridge_port *port,
				  struct sk_buff *skb)
{
	struct iphdr *iph = ip_hdr(skb);
	struct igmphdr *ih = igmp_hdr(skb);
	struct net_bridge_mdb_entry *mp;
	struct igmpv3_query *ih3;
	struct net_bridge_port_group *p;
	struct net_bridge_port_group **pp;
	unsigned long max_delay;
	unsigned long now = jiffies;
	__be32 group;
	int err = 0;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev) ||
	    (port && port->state == BR_STATE_DISABLED))
		goto out;

	br_multicast_query_received(br, port, !!iph->saddr);

	group = ih->group;

	if (skb->len == sizeof(*ih)) {
		max_delay = ih->code * (HZ / IGMP_TIMER_SCALE);

		if (!max_delay) {
			max_delay = 10 * HZ;
			group = 0;
		}
	} else {
		if (!pskb_may_pull(skb, sizeof(struct igmpv3_query))) {
			err = -EINVAL;
			goto out;
		}

		ih3 = igmpv3_query_hdr(skb);
		if (ih3->nsrcs)
			goto out;

		max_delay = ih3->code ? 1 :
			    IGMPV3_MRC(ih3->code) * (HZ / IGMP_TIMER_SCALE);
	}

	if (!group)
		goto out;

	mp = br_mdb_ip4_get(br->mdb, group);
	if (!mp)
		goto out;

	mod_timer(&mp->timer, now + br->multicast_membership_interval);
	mp->timer_armed = true;

	max_delay *= br->multicast_last_member_count;

	if (mp->mglist &&
	    (timer_pending(&mp->timer) ?
	     time_after(mp->timer.expires, now + max_delay) :
	     try_to_del_timer_sync(&mp->timer) >= 0))
		mod_timer(&mp->timer, now + max_delay);

	for (pp = &mp->ports; (p = *pp); pp = &p->next) {
		if (timer_pending(&p->timer) ?
		    time_after(p->timer.expires, now + max_delay) :
		    try_to_del_timer_sync(&p->timer) >= 0)
			mod_timer(&p->timer, now + max_delay);
	}

out:
	spin_unlock(&br->multicast_lock);
	return err;
}