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
struct tcphdr {int rst; int doff; int ack; scalar_t__ syn; scalar_t__ fin; int /*<<< orphan*/  check; int /*<<< orphan*/  seq; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  ip_summed; } ;
struct iphdr {int frag_off; int version; int ihl; int /*<<< orphan*/  ttl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; scalar_t__ check; int /*<<< orphan*/  protocol; scalar_t__ id; scalar_t__ tos; } ;
typedef  int /*<<< orphan*/  _otcph ;
struct TYPE_2__ {int rt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_DF ; 
 int /*<<< orphan*/  IP_OFFSET ; 
 scalar_t__ LL_MAX_HEADER ; 
 int /*<<< orphan*/  RTAX_HOPLIMIT ; 
 int RTCF_BROADCAST ; 
 int RTCF_MULTICAST ; 
 int /*<<< orphan*/  RTN_UNSPEC ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (struct tcphdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_metric (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dst_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_local_out (struct sk_buff*) ; 
 scalar_t__ ip_route_me_harder (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct tcphdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_attach (struct sk_buff*,struct sk_buff*) ; 
 scalar_t__ nf_ip_checksum (struct sk_buff*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,scalar_t__,int,struct tcphdr*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 TYPE_1__* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v4_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_reset(struct sk_buff *oldskb, int hook)
{
	struct sk_buff *nskb;
	const struct iphdr *oiph;
	struct iphdr *niph;
	const struct tcphdr *oth;
	struct tcphdr _otcph, *tcph;

	/* IP header checks: fragment. */
	if (ip_hdr(oldskb)->frag_off & htons(IP_OFFSET))
		return;

	oth = skb_header_pointer(oldskb, ip_hdrlen(oldskb),
				 sizeof(_otcph), &_otcph);
	if (oth == NULL)
		return;

	/* No RST for RST. */
	if (oth->rst)
		return;

	if (skb_rtable(oldskb)->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))
		return;

	/* Check checksum */
	if (nf_ip_checksum(oldskb, hook, ip_hdrlen(oldskb), IPPROTO_TCP))
		return;
	oiph = ip_hdr(oldskb);

	nskb = alloc_skb(sizeof(struct iphdr) + sizeof(struct tcphdr) +
			 LL_MAX_HEADER, GFP_ATOMIC);
	if (!nskb)
		return;

	skb_reserve(nskb, LL_MAX_HEADER);

	skb_reset_network_header(nskb);
	niph = (struct iphdr *)skb_put(nskb, sizeof(struct iphdr));
	niph->version	= 4;
	niph->ihl	= sizeof(struct iphdr) / 4;
	niph->tos	= 0;
	niph->id	= 0;
	niph->frag_off	= htons(IP_DF);
	niph->protocol	= IPPROTO_TCP;
	niph->check	= 0;
	niph->saddr	= oiph->daddr;
	niph->daddr	= oiph->saddr;

	tcph = (struct tcphdr *)skb_put(nskb, sizeof(struct tcphdr));
	memset(tcph, 0, sizeof(*tcph));
	tcph->source	= oth->dest;
	tcph->dest	= oth->source;
	tcph->doff	= sizeof(struct tcphdr) / 4;

	if (oth->ack)
		tcph->seq = oth->ack_seq;
	else {
		tcph->ack_seq = htonl(ntohl(oth->seq) + oth->syn + oth->fin +
				      oldskb->len - ip_hdrlen(oldskb) -
				      (oth->doff << 2));
		tcph->ack = 1;
	}

	tcph->rst	= 1;
	tcph->check	= tcp_v4_check(sizeof(struct tcphdr),
				       niph->saddr, niph->daddr,
				       csum_partial(tcph,
						    sizeof(struct tcphdr), 0));

	/* ip_route_me_harder expects skb->dst to be set */
	skb_dst_set(nskb, dst_clone(skb_dst(oldskb)));

	if (ip_route_me_harder(nskb, RTN_UNSPEC))
		goto free_nskb;

	niph->ttl	= dst_metric(skb_dst(nskb), RTAX_HOPLIMIT);
	nskb->ip_summed = CHECKSUM_NONE;

	/* "Never happens" */
	if (nskb->len > dst_mtu(skb_dst(nskb)))
		goto free_nskb;

	nf_ct_attach(nskb, oldskb);

	ip_local_out(nskb);
	return;

 free_nskb:
	kfree_skb(nskb);
}