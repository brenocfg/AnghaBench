#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {scalar_t__ mac_header; scalar_t__ network_header; TYPE_4__* dev; TYPE_3__* nf_bridge; } ;
struct TYPE_5__ {int /*<<< orphan*/  level; } ;
struct TYPE_6__ {TYPE_1__ log; } ;
struct nf_loginfo {TYPE_2__ u; } ;
struct net_device {char* name; } ;
struct TYPE_8__ {int hard_header_len; } ;
struct TYPE_7__ {struct net_device* physoutdev; struct net_device* physindev; } ;

/* Variables and functions */
 struct nf_loginfo default_loginfo ; 
 int /*<<< orphan*/  dump_packet (struct nf_loginfo const*,struct sk_buff const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_lock ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned char* skb_mac_header (struct sk_buff const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipt_log_packet(u_int8_t pf,
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
#ifdef CONFIG_BRIDGE_NETFILTER
	if (skb->nf_bridge) {
		const struct net_device *physindev;
		const struct net_device *physoutdev;

		physindev = skb->nf_bridge->physindev;
		if (physindev && in != physindev)
			printk("PHYSIN=%s ", physindev->name);
		physoutdev = skb->nf_bridge->physoutdev;
		if (physoutdev && out != physoutdev)
			printk("PHYSOUT=%s ", physoutdev->name);
	}
#endif

	if (in && !out) {
		/* MAC logging for input chain only. */
		printk("MAC=");
		if (skb->dev && skb->dev->hard_header_len
		    && skb->mac_header != skb->network_header) {
			int i;
			const unsigned char *p = skb_mac_header(skb);
			for (i = 0; i < skb->dev->hard_header_len; i++,p++)
				printk("%02x%c", *p,
				       i==skb->dev->hard_header_len - 1
				       ? ' ':':');
		} else
			printk(" ");
	}

	dump_packet(loginfo, skb, 0);
	printk("\n");
	spin_unlock_bh(&log_lock);
}