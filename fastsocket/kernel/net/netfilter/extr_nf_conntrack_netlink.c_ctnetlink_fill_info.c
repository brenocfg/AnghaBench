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
typedef  scalar_t__ u32 ;
struct sk_buff {int len; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {scalar_t__ res_id; int /*<<< orphan*/  version; int /*<<< orphan*/  nfgen_family; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int CTA_TUPLE_ORIG ; 
 int CTA_TUPLE_REPLY ; 
 int /*<<< orphan*/  IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  IP_CT_DIR_REPLY ; 
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int NFNL_SUBSYS_CTNETLINK ; 
 int NLA_F_NESTED ; 
 unsigned int NLM_F_MULTI ; 
 scalar_t__ ctnetlink_dump_counters (struct sk_buff*,struct nf_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ ctnetlink_dump_helpinfo (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_id (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_mark (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_master (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_nat_seq_adj (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_protoinfo (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_secmark (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_status (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_timeout (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_tuples (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ ctnetlink_dump_use (struct sk_buff*,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_tuple (struct nf_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,scalar_t__,scalar_t__,int,int,unsigned int) ; 

__attribute__((used)) static int
ctnetlink_fill_info(struct sk_buff *skb, u32 pid, u32 seq,
		    int event, struct nf_conn *ct)
{
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfmsg;
	struct nlattr *nest_parms;
	unsigned int flags = pid ? NLM_F_MULTI : 0;

	event |= NFNL_SUBSYS_CTNETLINK << 8;
	nlh = nlmsg_put(skb, pid, seq, event, sizeof(*nfmsg), flags);
	if (nlh == NULL)
		goto nlmsg_failure;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family = nf_ct_l3num(ct);
	nfmsg->version      = NFNETLINK_V0;
	nfmsg->res_id	    = 0;

	nest_parms = nla_nest_start(skb, CTA_TUPLE_ORIG | NLA_F_NESTED);
	if (!nest_parms)
		goto nla_put_failure;
	if (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_DIR_ORIGINAL)) < 0)
		goto nla_put_failure;
	nla_nest_end(skb, nest_parms);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_REPLY | NLA_F_NESTED);
	if (!nest_parms)
		goto nla_put_failure;
	if (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_DIR_REPLY)) < 0)
		goto nla_put_failure;
	nla_nest_end(skb, nest_parms);

	if (ctnetlink_dump_status(skb, ct) < 0 ||
	    ctnetlink_dump_timeout(skb, ct) < 0 ||
	    ctnetlink_dump_counters(skb, ct, IP_CT_DIR_ORIGINAL) < 0 ||
	    ctnetlink_dump_counters(skb, ct, IP_CT_DIR_REPLY) < 0 ||
	    ctnetlink_dump_protoinfo(skb, ct) < 0 ||
	    ctnetlink_dump_helpinfo(skb, ct) < 0 ||
	    ctnetlink_dump_mark(skb, ct) < 0 ||
	    ctnetlink_dump_secmark(skb, ct) < 0 ||
	    ctnetlink_dump_id(skb, ct) < 0 ||
	    ctnetlink_dump_use(skb, ct) < 0 ||
	    ctnetlink_dump_master(skb, ct) < 0 ||
	    ctnetlink_dump_nat_seq_adj(skb, ct) < 0)
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -1;
}