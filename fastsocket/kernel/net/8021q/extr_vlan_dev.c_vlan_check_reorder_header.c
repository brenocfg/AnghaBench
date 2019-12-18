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
struct sk_buff {int /*<<< orphan*/  mac_header; scalar_t__ data; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 int VLAN_FLAG_REORDER_HDR ; 
 scalar_t__ VLAN_HLEN ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 scalar_t__ skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 TYPE_1__* vlan_dev_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sk_buff *vlan_check_reorder_header(struct sk_buff *skb)
{
	if (vlan_dev_info(skb->dev)->flags & VLAN_FLAG_REORDER_HDR) {
		if (skb_cow(skb, skb_headroom(skb)) < 0)
			skb = NULL;
		if (skb) {
			/* Lifted from Gleb's VLAN code... */
			memmove(skb->data - ETH_HLEN,
				skb->data - VLAN_ETH_HLEN, 12);
			skb->mac_header += VLAN_HLEN;
		}
	}

	return skb;
}