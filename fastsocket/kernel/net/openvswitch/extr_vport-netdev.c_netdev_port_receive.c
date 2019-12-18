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
struct vport {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_skb_postpush_rcsum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_vport_receive (struct vport*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_warn_if_lro (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void netdev_port_receive(struct vport *vport, struct sk_buff *skb)
{
	if (unlikely(!vport))
		goto error;

	if (unlikely(skb_warn_if_lro(skb)))
		goto error;

	/* Make our own copy of the packet.  Otherwise we will mangle the
	 * packet for anyone who came before us (e.g. tcpdump via AF_PACKET).
	 */
	skb = skb_share_check(skb, GFP_ATOMIC);
	if (unlikely(!skb))
		return;

	skb_push(skb, ETH_HLEN);
	ovs_skb_postpush_rcsum(skb, skb->data, ETH_HLEN);

	ovs_vport_receive(vport, skb, NULL);
	return;

error:
	kfree_skb(skb);
}