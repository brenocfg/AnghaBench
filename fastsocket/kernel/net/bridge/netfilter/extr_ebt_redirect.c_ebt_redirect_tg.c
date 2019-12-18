#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xt_target_param {scalar_t__ hooknum; TYPE_2__* in; struct ebt_redirect_info* targinfo; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; } ;
struct ebt_redirect_info {unsigned int target; } ;
struct TYPE_10__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_9__ {TYPE_3__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; TYPE_1__* br_port; } ;
struct TYPE_6__ {TYPE_4__* br; } ;

/* Variables and functions */
 unsigned int EBT_DROP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NF_BR_BROUTING ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 TYPE_5__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ebt_redirect_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct ebt_redirect_info *info = par->targinfo;

	if (!skb_make_writable(skb, 0))
		return EBT_DROP;

	if (par->hooknum != NF_BR_BROUTING)
		memcpy(eth_hdr(skb)->h_dest,
		       par->in->br_port->br->dev->dev_addr, ETH_ALEN);
	else
		memcpy(eth_hdr(skb)->h_dest, par->in->dev_addr, ETH_ALEN);
	skb->pkt_type = PACKET_HOST;
	return info->target;
}