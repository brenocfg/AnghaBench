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
struct tcphdr {int th_off; scalar_t__ th_urp; scalar_t__ th_win; scalar_t__ th_flags; scalar_t__ th_x2; scalar_t__ th_ack; scalar_t__ th_seq; int /*<<< orphan*/  th_dport; int /*<<< orphan*/  th_sport; int /*<<< orphan*/  th_sum; } ;
struct tcpcb {struct inpcb* t_inpcb; } ;
struct ip6_hdr {int ip6_flow; int ip6_vfc; int ip6_nxt; int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; scalar_t__ ip6_hlim; int /*<<< orphan*/  ip6_plen; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct ip {int ip_p; TYPE_2__ ip_dst; TYPE_1__ ip_src; scalar_t__ ip_sum; scalar_t__ ip_ttl; scalar_t__ ip_off; scalar_t__ ip_id; scalar_t__ ip_len; scalar_t__ ip_tos; int /*<<< orphan*/  ip_vhl; } ;
struct inpcb {int inp_vflag; int inp_flow; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; TYPE_2__ inp_faddr; TYPE_1__ inp_laddr; int /*<<< orphan*/  in6p_faddr; int /*<<< orphan*/  in6p_laddr; } ;

/* Variables and functions */
 int INP_IPV6 ; 
 int IPPROTO_TCP ; 
 int IPV6_FLOWINFO_MASK ; 
 int IPV6_VERSION ; 
 int IPV6_VERSION_MASK ; 
 int /*<<< orphan*/  IP_VHL_BORING ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  in6_pseudo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_pseudo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tcp_fillheaders(struct tcpcb *tp, void *ip_ptr, void *tcp_ptr)
{
	struct inpcb *inp = tp->t_inpcb;
	struct tcphdr *tcp_hdr = (struct tcphdr *)tcp_ptr;

#if INET6
	if ((inp->inp_vflag & INP_IPV6) != 0) {
		struct ip6_hdr *ip6;

		ip6 = (struct ip6_hdr *)ip_ptr;
		ip6->ip6_flow = (ip6->ip6_flow & ~IPV6_FLOWINFO_MASK) |
			(inp->inp_flow & IPV6_FLOWINFO_MASK);
		ip6->ip6_vfc = (ip6->ip6_vfc & ~IPV6_VERSION_MASK) |
			(IPV6_VERSION & IPV6_VERSION_MASK);
		ip6->ip6_plen = htons(sizeof(struct tcphdr));
		ip6->ip6_nxt = IPPROTO_TCP;
		ip6->ip6_hlim = 0;
		ip6->ip6_src = inp->in6p_laddr;
		ip6->ip6_dst = inp->in6p_faddr;
		tcp_hdr->th_sum = in6_pseudo(&inp->in6p_laddr, &inp->in6p_faddr,
		    htonl(sizeof (struct tcphdr) + IPPROTO_TCP));
	} else
#endif
	{
		struct ip *ip = (struct ip *) ip_ptr;

		ip->ip_vhl = IP_VHL_BORING;
		ip->ip_tos = 0;
		ip->ip_len = 0;
		ip->ip_id = 0;
		ip->ip_off = 0;
		ip->ip_ttl = 0;
		ip->ip_sum = 0;
		ip->ip_p = IPPROTO_TCP;
		ip->ip_src = inp->inp_laddr;
		ip->ip_dst = inp->inp_faddr;
		tcp_hdr->th_sum =
		    in_pseudo(ip->ip_src.s_addr, ip->ip_dst.s_addr,
		    htons(sizeof(struct tcphdr) + IPPROTO_TCP));
	}

	tcp_hdr->th_sport = inp->inp_lport;
	tcp_hdr->th_dport = inp->inp_fport;
	tcp_hdr->th_seq = 0;
	tcp_hdr->th_ack = 0;
	tcp_hdr->th_x2 = 0;
	tcp_hdr->th_off = 5;
	tcp_hdr->th_flags = 0;
	tcp_hdr->th_win = 0;
	tcp_hdr->th_urp = 0;
}