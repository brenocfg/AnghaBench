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
typedef  int u_int32_t ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int mark; int /*<<< orphan*/  dev; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  _hdr ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_LOOKUP_ESTABLISHED ; 
 int /*<<< orphan*/  NFT_LOOKUP_LISTENER ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 scalar_t__ TCP_TIME_WAIT ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_tproxy_assign_sock (struct sk_buff*,struct sock*) ; 
 struct sock* nf_tproxy_get_sock_v4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct udphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct udphdr*) ; 
 struct sock* tproxy_handle_time_wait4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  tproxy_laddr4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tproxy_sk_is_transparent (struct sock*) ; 

__attribute__((used)) static unsigned int
tproxy_tg4(struct sk_buff *skb, __be32 laddr, __be16 lport,
	   u_int32_t mark_mask, u_int32_t mark_value)
{
	const struct iphdr *iph = ip_hdr(skb);
	struct udphdr _hdr, *hp;
	struct sock *sk;

	hp = skb_header_pointer(skb, ip_hdrlen(skb), sizeof(_hdr), &_hdr);
	if (hp == NULL)
		return NF_DROP;

	/* check if there's an ongoing connection on the packet
	 * addresses, this happens if the redirect already happened
	 * and the current packet belongs to an already established
	 * connection */
	sk = nf_tproxy_get_sock_v4(dev_net(skb->dev), iph->protocol,
				   iph->saddr, iph->daddr,
				   hp->source, hp->dest,
				   skb->dev, NFT_LOOKUP_ESTABLISHED);

	laddr = tproxy_laddr4(skb, laddr, iph->daddr);
	if (!lport)
		lport = hp->dest;

	/* UDP has no TCP_TIME_WAIT state, so we never enter here */
	if (sk && sk->sk_state == TCP_TIME_WAIT)
		/* reopening a TIME_WAIT connection needs special handling */
		sk = tproxy_handle_time_wait4(skb, laddr, lport, sk);
	else if (!sk)
		/* no, there's no established connection, check if
		 * there's a listener on the redirected addr/port */
		sk = nf_tproxy_get_sock_v4(dev_net(skb->dev), iph->protocol,
					   iph->saddr, laddr,
					   hp->source, lport,
					   skb->dev, NFT_LOOKUP_LISTENER);

	/* NOTE: assign_sock consumes our sk reference */
	if (sk && tproxy_sk_is_transparent(sk)) {
		/* This should be in a separate target, but we don't do multiple
		   targets on the same rule yet */
		skb->mark = (skb->mark & ~mark_mask) ^ mark_value;

		pr_debug("redirecting: proto %hhu %pI4:%hu -> %pI4:%hu, mark: %x\n",
			 iph->protocol, &iph->daddr, ntohs(hp->dest),
			 &laddr, ntohs(lport), skb->mark);

		nf_tproxy_assign_sock(skb, sk);
		return NF_ACCEPT;
	}

	pr_debug("no socket, dropping: proto %hhu %pI4:%hu -> %pI4:%hu, mark: %x\n",
		 iph->protocol, &iph->saddr, ntohs(hp->source),
		 &iph->daddr, ntohs(hp->dest), skb->mark);
	return NF_DROP;
}