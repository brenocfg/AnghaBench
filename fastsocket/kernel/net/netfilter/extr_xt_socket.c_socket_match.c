#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct xt_socket_mtinfo1 {int flags; } ;
struct xt_match_param {int /*<<< orphan*/  in; } ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct nf_conn {int status; TYPE_7__* tuplehash; } ;
struct iphdr {scalar_t__ protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  _hdr ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_18__ {scalar_t__ rcv_saddr; scalar_t__ transparent; } ;
struct TYPE_17__ {scalar_t__ tw_transparent; } ;
struct TYPE_12__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {int /*<<< orphan*/  port; } ;
struct TYPE_13__ {TYPE_3__ udp; TYPE_2__ tcp; } ;
struct TYPE_10__ {int /*<<< orphan*/  ip; } ;
struct TYPE_14__ {TYPE_4__ u; TYPE_1__ u3; } ;
struct TYPE_15__ {TYPE_5__ src; } ;
struct TYPE_16__ {TYPE_6__ tuple; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int IPS_SRC_NAT_DONE ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 int IP_CT_ESTABLISHED ; 
 int IP_CT_IS_REPLY ; 
 int IP_CT_RELATED ; 
 int /*<<< orphan*/  NFT_LOOKUP_ANY ; 
 scalar_t__ TCP_TIME_WAIT ; 
 int XT_SOCKET_TRANSPARENT ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ extract_icmp4_fields (struct sk_buff const*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_9__* inet_sk (struct sock*) ; 
 TYPE_8__* inet_twsk (struct sock*) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff const*) ; 
 struct nf_conn const nf_conntrack_untracked ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 
 struct sock* nf_tproxy_get_sock_v4 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sock*) ; 
 struct udphdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct udphdr*) ; 
 int /*<<< orphan*/  xt_socket_put_sk (struct sock*) ; 

__attribute__((used)) static bool
socket_match(const struct sk_buff *skb, const struct xt_match_param *par,
	     const struct xt_socket_mtinfo1 *info)
{
	const struct iphdr *iph = ip_hdr(skb);
	struct udphdr _hdr, *hp = NULL;
	struct sock *sk;
	__be32 daddr, saddr;
	__be16 dport, sport;
	u8 protocol;
#ifdef XT_SOCKET_HAVE_CONNTRACK
	struct nf_conn const *ct;
	enum ip_conntrack_info ctinfo;
#endif

	if (iph->protocol == IPPROTO_UDP || iph->protocol == IPPROTO_TCP) {
		hp = skb_header_pointer(skb, ip_hdrlen(skb),
					sizeof(_hdr), &_hdr);
		if (hp == NULL)
			return false;

		protocol = iph->protocol;
		saddr = iph->saddr;
		sport = hp->source;
		daddr = iph->daddr;
		dport = hp->dest;

	} else if (iph->protocol == IPPROTO_ICMP) {
		if (extract_icmp4_fields(skb, &protocol, &saddr, &daddr,
					&sport, &dport))
			return false;
	} else {
		return false;
	}

#ifdef XT_SOCKET_HAVE_CONNTRACK
	/* Do the lookup with the original socket address in case this is a
	 * reply packet of an established SNAT-ted connection. */

	ct = nf_ct_get(skb, &ctinfo);
	if (ct && (ct != &nf_conntrack_untracked) &&
	    ((iph->protocol != IPPROTO_ICMP &&
	      ctinfo == IP_CT_IS_REPLY + IP_CT_ESTABLISHED) ||
	     (iph->protocol == IPPROTO_ICMP &&
	      ctinfo == IP_CT_IS_REPLY + IP_CT_RELATED)) &&
	    (ct->status & IPS_SRC_NAT_DONE)) {

		daddr = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
		dport = (iph->protocol == IPPROTO_TCP) ?
			ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.tcp.port :
			ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.udp.port;
	}
#endif

	sk = nf_tproxy_get_sock_v4(dev_net(skb->dev), protocol,
				   saddr, daddr, sport, dport, par->in, NFT_LOOKUP_ANY);
	if (sk != NULL) {
		bool wildcard;
		bool transparent = true;

		/* Ignore sockets listening on INADDR_ANY */
		wildcard = (sk->sk_state != TCP_TIME_WAIT &&
			    inet_sk(sk)->rcv_saddr == 0);

		/* Ignore non-transparent sockets,
		   if XT_SOCKET_TRANSPARENT is used */
		if (info && info->flags & XT_SOCKET_TRANSPARENT)
			transparent = ((sk->sk_state != TCP_TIME_WAIT &&
					inet_sk(sk)->transparent) ||
				       (sk->sk_state == TCP_TIME_WAIT &&
					inet_twsk(sk)->tw_transparent));

		xt_socket_put_sk(sk);

		if (wildcard || !transparent)
			sk = NULL;
	}

	pr_debug("proto %hhu %pI4:%hu -> %pI4:%hu (orig %pI4:%hu) sock %p\n",
		 protocol, &saddr, ntohs(sport),
		 &daddr, ntohs(dport),
		 &iph->daddr, hp ? ntohs(hp->dest) : 0, sk);

	return (sk != NULL);
}