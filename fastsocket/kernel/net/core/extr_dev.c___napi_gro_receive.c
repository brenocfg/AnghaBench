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
struct sk_buff {TYPE_1__* dev; struct sk_buff* next; } ;
struct napi_struct {struct sk_buff* gro_list; } ;
typedef  int /*<<< orphan*/  gro_result_t ;
struct TYPE_4__ {int same_flow; scalar_t__ flush; } ;
struct TYPE_3__ {unsigned int hard_header_len; } ;

/* Variables and functions */
 unsigned int ETH_HLEN ; 
 TYPE_2__* NAPI_GRO_CB (struct sk_buff*) ; 
 unsigned long compare_ether_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 unsigned long memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_gro_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static gro_result_t
__napi_gro_receive(struct napi_struct *napi, struct sk_buff *skb)
{
	struct sk_buff *p;
	unsigned int maclen = skb->dev->hard_header_len;

	for (p = napi->gro_list; p; p = p->next) {
		unsigned long diffs;

		diffs = (unsigned long)p->dev ^ (unsigned long)skb->dev;
		if (maclen == ETH_HLEN)
			diffs |= compare_ether_header(skb_mac_header(p),
						      skb_gro_mac_header(skb));
		else if (!diffs)
			diffs = memcmp(skb_mac_header(p),
				       skb_gro_mac_header(skb),
				       maclen);
		NAPI_GRO_CB(p)->same_flow = !diffs;
		NAPI_GRO_CB(p)->flush = 0;
	}

	return dev_gro_receive(napi, skb);
}