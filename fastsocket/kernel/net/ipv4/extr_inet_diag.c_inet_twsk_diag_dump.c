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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {TYPE_3__* nlh; int /*<<< orphan*/  skb; } ;
struct inet_timewait_sock {scalar_t__ tw_family; int /*<<< orphan*/  tw_dport; int /*<<< orphan*/  tw_num; int /*<<< orphan*/  tw_daddr; int /*<<< orphan*/  tw_rcv_saddr; } ;
struct inet_diag_req {int /*<<< orphan*/  idiag_ext; } ;
struct inet_diag_entry {scalar_t__ family; scalar_t__ userlocks; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/ * daddr; int /*<<< orphan*/ * saddr; } ;
struct TYPE_9__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_8__ {int /*<<< orphan*/ * s6_addr32; } ;
struct inet6_timewait_sock {TYPE_2__ tw_v6_daddr; TYPE_1__ tw_v6_rcv_saddr; } ;
struct TYPE_11__ {int /*<<< orphan*/  pid; } ;
struct TYPE_10__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  INET_DIAG_REQ_BYTECODE ; 
 TYPE_7__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 struct inet_diag_req* NLMSG_DATA (TYPE_3__*) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 struct inet6_timewait_sock* inet6_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_diag_bc_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inet_diag_entry*) ; 
 int inet_twsk_diag_fill (struct inet_timewait_sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr const*) ; 
 scalar_t__ nlmsg_attrlen (TYPE_3__*,int) ; 
 struct nlattr* nlmsg_find_attr (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_twsk_diag_dump(struct inet_timewait_sock *tw,
			       struct sk_buff *skb,
			       struct netlink_callback *cb)
{
	struct inet_diag_req *r = NLMSG_DATA(cb->nlh);

	if (nlmsg_attrlen(cb->nlh, sizeof(*r))) {
		struct inet_diag_entry entry;
		const struct nlattr *bc = nlmsg_find_attr(cb->nlh,
							  sizeof(*r),
							  INET_DIAG_REQ_BYTECODE);

		entry.family = tw->tw_family;
#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
		if (tw->tw_family == AF_INET6) {
			struct inet6_timewait_sock *tw6 =
						inet6_twsk((struct sock *)tw);
			entry.saddr = tw6->tw_v6_rcv_saddr.s6_addr32;
			entry.daddr = tw6->tw_v6_daddr.s6_addr32;
		} else
#endif
		{
			entry.saddr = &tw->tw_rcv_saddr;
			entry.daddr = &tw->tw_daddr;
		}
		entry.sport = tw->tw_num;
		entry.dport = ntohs(tw->tw_dport);
		entry.userlocks = 0;

		if (!inet_diag_bc_run(nla_data(bc), nla_len(bc), &entry))
			return 0;
	}

	return inet_twsk_diag_fill(tw, skb, r->idiag_ext,
				   NETLINK_CB(cb->skb).pid,
				   cb->nlh->nlmsg_seq, NLM_F_MULTI, cb->nlh);
}