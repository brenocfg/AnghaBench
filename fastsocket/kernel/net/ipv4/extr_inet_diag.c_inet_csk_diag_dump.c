#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_family; int /*<<< orphan*/  sk_userlocks; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {TYPE_3__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_9__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_8__ {int /*<<< orphan*/ * s6_addr32; } ;
struct ipv6_pinfo {TYPE_2__ daddr; TYPE_1__ rcv_saddr; } ;
struct inet_sock {int /*<<< orphan*/  dport; int /*<<< orphan*/  num; int /*<<< orphan*/  daddr; int /*<<< orphan*/  rcv_saddr; } ;
struct inet_diag_req {int /*<<< orphan*/  idiag_ext; } ;
struct inet_diag_entry {scalar_t__ family; int /*<<< orphan*/  userlocks; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/ * daddr; int /*<<< orphan*/ * saddr; } ;
struct TYPE_11__ {int /*<<< orphan*/  pid; } ;
struct TYPE_10__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  INET_DIAG_REQ_BYTECODE ; 
 TYPE_7__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 struct inet_diag_req* NLMSG_DATA (TYPE_3__*) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int inet_csk_diag_fill (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  inet_diag_bc_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inet_diag_entry*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr const*) ; 
 scalar_t__ nlmsg_attrlen (TYPE_3__*,int) ; 
 struct nlattr* nlmsg_find_attr (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_csk_diag_dump(struct sock *sk,
			      struct sk_buff *skb,
			      struct netlink_callback *cb)
{
	struct inet_diag_req *r = NLMSG_DATA(cb->nlh);

	if (nlmsg_attrlen(cb->nlh, sizeof(*r))) {
		struct inet_diag_entry entry;
		const struct nlattr *bc = nlmsg_find_attr(cb->nlh,
							  sizeof(*r),
							  INET_DIAG_REQ_BYTECODE);
		struct inet_sock *inet = inet_sk(sk);

		entry.family = sk->sk_family;
#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
		if (entry.family == AF_INET6) {
			struct ipv6_pinfo *np = inet6_sk(sk);

			entry.saddr = np->rcv_saddr.s6_addr32;
			entry.daddr = np->daddr.s6_addr32;
		} else
#endif
		{
			entry.saddr = &inet->rcv_saddr;
			entry.daddr = &inet->daddr;
		}
		entry.sport = inet->num;
		entry.dport = ntohs(inet->dport);
		entry.userlocks = sk->sk_userlocks;

		if (!inet_diag_bc_run(nla_data(bc), nla_len(bc), &entry))
			return 0;
	}

	return inet_csk_diag_fill(sk, skb, r->idiag_ext,
				  NETLINK_CB(cb->skb).pid,
				  cb->nlh->nlmsg_seq, NLM_F_MULTI, cb->nlh);
}