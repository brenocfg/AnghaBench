#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int local_df; } ;
struct TYPE_9__ {TYPE_1__* dev; } ;
struct TYPE_7__ {TYPE_4__ dst; } ;
struct rtable {TYPE_2__ u; } ;
struct iphdr {int ihl; int frag_off; int /*<<< orphan*/  daddr; int /*<<< orphan*/  tos; } ;
struct ip_vs_protocol {int /*<<< orphan*/  (* dnat_handler ) (struct sk_buff*,struct ip_vs_protocol*,struct ip_vs_conn*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct ip_vs_conn {int flags; TYPE_3__ daddr; } ;
typedef  int /*<<< orphan*/  _pt ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {int /*<<< orphan*/  hard_header_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterFunction (int) ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_FRAG_NEEDED ; 
 int /*<<< orphan*/  IP_DF ; 
 int IP_VS_CONN_F_NO_CPORT ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_VS_DBG_PKT (int,struct ip_vs_protocol*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IP_VS_DBG_RL_PKT (int /*<<< orphan*/ ,struct ip_vs_protocol*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IP_VS_XMIT (int /*<<< orphan*/ ,struct sk_buff*,struct rtable*) ; 
 int /*<<< orphan*/  LeaveFunction (int) ; 
 int NF_STOLEN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 struct rtable* __ip_vs_get_out_rt (struct sk_buff*,struct ip_vs_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_link_failure (struct sk_buff*) ; 
 int dst_mtu (TYPE_4__*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  ip_vs_conn_fill_cport (struct ip_vs_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_4__*) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct ip_vs_protocol*,struct ip_vs_conn*) ; 
 scalar_t__ unlikely (int) ; 

int
ip_vs_nat_xmit(struct sk_buff *skb, struct ip_vs_conn *cp,
	       struct ip_vs_protocol *pp)
{
	struct rtable *rt;		/* Route to the other host */
	int mtu;
	struct iphdr *iph = ip_hdr(skb);

	EnterFunction(10);

	/* check if it is a connection of no-client-port */
	if (unlikely(cp->flags & IP_VS_CONN_F_NO_CPORT)) {
		__be16 _pt, *p;
		p = skb_header_pointer(skb, iph->ihl*4, sizeof(_pt), &_pt);
		if (p == NULL)
			goto tx_error;
		ip_vs_conn_fill_cport(cp, *p);
		IP_VS_DBG(10, "filled cport=%d\n", ntohs(*p));
	}

	if (!(rt = __ip_vs_get_out_rt(skb, cp, RT_TOS(iph->tos))))
		goto tx_error_icmp;

	/* MTU checking */
	mtu = dst_mtu(&rt->u.dst);
	if ((skb->len > mtu) && (iph->frag_off & htons(IP_DF)) &&
	    !skb_is_gso(skb)) {
		ip_rt_put(rt);
		icmp_send(skb, ICMP_DEST_UNREACH,ICMP_FRAG_NEEDED, htonl(mtu));
		IP_VS_DBG_RL_PKT(0, pp, skb, 0, "ip_vs_nat_xmit(): frag needed for");
		goto tx_error;
	}

	/* copy-on-write the packet before mangling it */
	if (!skb_make_writable(skb, sizeof(struct iphdr)))
		goto tx_error_put;

	if (skb_cow(skb, rt->u.dst.dev->hard_header_len))
		goto tx_error_put;

	/* drop old route */
	skb_dst_drop(skb);
	skb_dst_set(skb, &rt->u.dst);

	/* mangle the packet */
	if (pp->dnat_handler && !pp->dnat_handler(skb, pp, cp))
		goto tx_error;
	ip_hdr(skb)->daddr = cp->daddr.ip;
	ip_send_check(ip_hdr(skb));

	IP_VS_DBG_PKT(10, pp, skb, 0, "After DNAT");

	/* FIXME: when application helper enlarges the packet and the length
	   is larger than the MTU of outgoing device, there will be still
	   MTU problem. */

	/* Another hack: avoid icmp_send in ip_fragment */
	skb->local_df = 1;

	IP_VS_XMIT(PF_INET, skb, rt);

	LeaveFunction(10);
	return NF_STOLEN;

  tx_error_icmp:
	dst_link_failure(skb);
  tx_error:
	LeaveFunction(10);
	kfree_skb(skb);
	return NF_STOLEN;
  tx_error_put:
	ip_rt_put(rt);
	goto tx_error;
}