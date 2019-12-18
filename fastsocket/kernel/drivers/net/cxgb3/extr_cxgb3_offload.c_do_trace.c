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
struct t3cdev {int /*<<< orphan*/  lldev; } ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; } ;
struct cpl_trace_pkt {int dummy; } ;

/* Variables and functions */
 struct cpl_trace_pkt* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int do_trace(struct t3cdev *dev, struct sk_buff *skb)
{
	struct cpl_trace_pkt *p = cplhdr(skb);

	skb->protocol = htons(0xffff);
	skb->dev = dev->lldev;
	skb_pull(skb, sizeof(*p));
	skb_reset_mac_header(skb);
	netif_receive_skb(skb);
	return 0;
}