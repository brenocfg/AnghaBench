#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {scalar_t__ mac_header; scalar_t__ network_header; unsigned char const* head; TYPE_3__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  level; } ;
struct TYPE_5__ {TYPE_1__ log; } ;
struct nf_loginfo {TYPE_2__ u; } ;
struct net_device {char* name; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {unsigned int hard_header_len; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_SIT ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 struct nf_loginfo default_loginfo ; 
 int /*<<< orphan*/  dump_packet (struct nf_loginfo const*,struct sk_buff const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_lock ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned char* skb_mac_header (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ip6t_log_packet(u_int8_t pf,
		unsigned int hooknum,
		const struct sk_buff *skb,
		const struct net_device *in,
		const struct net_device *out,
		const struct nf_loginfo *loginfo,
		const char *prefix)
{
	if (!loginfo)
		loginfo = &default_loginfo;

	spin_lock_bh(&log_lock);
	printk("<%d>%sIN=%s OUT=%s ", loginfo->u.log.level,
		prefix,
		in ? in->name : "",
		out ? out->name : "");
	if (in && !out) {
		unsigned int len;
		/* MAC logging for input chain only. */
		printk("MAC=");
		if (skb->dev && (len = skb->dev->hard_header_len) &&
		    skb->mac_header != skb->network_header) {
			const unsigned char *p = skb_mac_header(skb);
			int i;

			if (skb->dev->type == ARPHRD_SIT &&
			    (p -= ETH_HLEN) < skb->head)
				p = NULL;

			if (p != NULL) {
				for (i = 0; i < len; i++)
					printk("%02x%s", p[i],
					       i == len - 1 ? "" : ":");
			}
			printk(" ");

			if (skb->dev->type == ARPHRD_SIT) {
				const struct iphdr *iph =
					(struct iphdr *)skb_mac_header(skb);
				printk("TUNNEL=%pI4->%pI4 ",
				       &iph->saddr, &iph->daddr);
			}
		} else
			printk(" ");
	}

	dump_packet(loginfo, skb, skb_network_offset(skb), 1);
	printk("\n");
	spin_unlock_bh(&log_lock);
}