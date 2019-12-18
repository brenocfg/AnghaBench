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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned int u16 ;
struct sk_buff {struct sk_buff* next; } ;
struct net_protocol {struct sk_buff** (* gro_receive ) (struct sk_buff**,struct sk_buff*) ;} ;
struct net_offload {struct sk_buff** (* gro_receive ) (struct sk_buff**,struct sk_buff*) ;} ;
struct iphdr {int protocol; int tos; int saddr; int daddr; unsigned int ttl; int /*<<< orphan*/  id; int /*<<< orphan*/  ihl; } ;
struct TYPE_2__ {unsigned int flush; scalar_t__ count; scalar_t__ same_flow; } ;

/* Variables and functions */
 unsigned int IP_DF ; 
 int MAX_INET_PROTOS ; 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/ * inet_offloads ; 
 int /*<<< orphan*/ * inet_protos ; 
 int ip_fast_csum (int*,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iphdr* skb_gro_header_fast (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_gro_header_hard (struct sk_buff*,unsigned int) ; 
 struct iphdr* skb_gro_header_slow (struct sk_buff*,unsigned int,unsigned int) ; 
 unsigned int skb_gro_len (struct sk_buff*) ; 
 unsigned int skb_gro_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gro_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,unsigned int) ; 
 struct sk_buff** stub1 (struct sk_buff**,struct sk_buff*) ; 
 struct sk_buff** stub2 (struct sk_buff**,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff **inet_gro_receive(struct sk_buff **head,
					 struct sk_buff *skb)
{
	const struct net_offload *ops;
	const struct net_protocol *proto_ops = NULL;
	struct sk_buff **pp = NULL;
	struct sk_buff *p;
	struct iphdr *iph;
	unsigned int hlen;
	unsigned int off;
	unsigned int id;
	int flush = 1;
	int proto;

	off = skb_gro_offset(skb);
	hlen = off + sizeof(*iph);
	iph = skb_gro_header_fast(skb, off);
	if (skb_gro_header_hard(skb, hlen)) {
		iph = skb_gro_header_slow(skb, hlen, off);
		if (unlikely(!iph))
			goto out;
	}

	proto = iph->protocol & (MAX_INET_PROTOS - 1);

	rcu_read_lock();
	ops = rcu_dereference(inet_offloads[proto]);
	if (!ops || !ops->gro_receive) {
		/* Try the protocols array */
		proto_ops = rcu_dereference(inet_protos[proto]);
		if (!proto_ops || !proto_ops->gro_receive)
			goto out_unlock;

		ops = NULL;
	}

	if (*(u8 *)iph != 0x45)
		goto out_unlock;

	if (unlikely(ip_fast_csum((u8 *)iph, iph->ihl)))
		goto out_unlock;

	id = ntohl(*(u32 *)&iph->id);
	flush = (u16)((ntohl(*(u32 *)iph) ^ skb_gro_len(skb)) | (id ^ IP_DF));
	id >>= 16;

	for (p = *head; p; p = p->next) {
		struct iphdr *iph2;

		if (!NAPI_GRO_CB(p)->same_flow)
			continue;

		iph2 = ip_hdr(p);

		if ((iph->protocol ^ iph2->protocol) |
		    (iph->tos ^ iph2->tos) |
		    (iph->saddr ^ iph2->saddr) |
		    (iph->daddr ^ iph2->daddr)) {
			NAPI_GRO_CB(p)->same_flow = 0;
			continue;
		}

		/* All fields must match except length and checksum. */
		NAPI_GRO_CB(p)->flush |=
			(iph->ttl ^ iph2->ttl) |
			((u16)(ntohs(iph2->id) + NAPI_GRO_CB(p)->count) ^ id);

		NAPI_GRO_CB(p)->flush |= flush;
	}

	NAPI_GRO_CB(skb)->flush |= flush;
	skb_gro_pull(skb, sizeof(*iph));
	skb_set_transport_header(skb, skb_gro_offset(skb));

	if (ops)
		pp = ops->gro_receive(head, skb);
	else
		pp = proto_ops->gro_receive(head, skb);

out_unlock:
	rcu_read_unlock();

out:
	NAPI_GRO_CB(skb)->flush |= flush;

	return pp;
}