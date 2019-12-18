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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 size_t CTA_ID ; 
 size_t CTA_TUPLE_ORIG ; 
 size_t CTA_TUPLE_REPLY ; 
 int ENOENT ; 
 int /*<<< orphan*/  IPCT_DESTROY ; 
 int /*<<< orphan*/  IPS_DYING_BIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int ctnetlink_parse_tuple (struct nlattr const* const*,struct nf_conntrack_tuple*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ nf_conntrack_event_report (int /*<<< orphan*/ ,struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (int /*<<< orphan*/ *,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_conntrack_flush_report (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_delete_from_lists (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_insert_dying_list (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_kill (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  nlmsg_report (struct nlmsghdr const*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctnetlink_del_conntrack(struct sock *ctnl, struct sk_buff *skb,
			const struct nlmsghdr *nlh,
			const struct nlattr * const cda[])
{
	struct nf_conntrack_tuple_hash *h;
	struct nf_conntrack_tuple tuple;
	struct nf_conn *ct;
	struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u_int8_t u3 = nfmsg->nfgen_family;
	int err = 0;

	if (cda[CTA_TUPLE_ORIG])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_TUPLE_ORIG, u3);
	else if (cda[CTA_TUPLE_REPLY])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_TUPLE_REPLY, u3);
	else {
		/* Flush the whole table */
		nf_conntrack_flush_report(&init_net,
					 NETLINK_CB(skb).pid,
					 nlmsg_report(nlh));
		return 0;
	}

	if (err < 0)
		return err;

	h = nf_conntrack_find_get(&init_net, &tuple);
	if (!h)
		return -ENOENT;

	ct = nf_ct_tuplehash_to_ctrack(h);

	if (cda[CTA_ID]) {
		u_int32_t id = ntohl(nla_get_be32(cda[CTA_ID]));
		if (id != (u32)(unsigned long)ct) {
			nf_ct_put(ct);
			return -ENOENT;
		}
	}

	if (nf_conntrack_event_report(IPCT_DESTROY, ct,
				      NETLINK_CB(skb).pid,
				      nlmsg_report(nlh)) < 0) {
		nf_ct_delete_from_lists(ct);
		/* we failed to report the event, try later */
		nf_ct_insert_dying_list(ct);
		nf_ct_put(ct);
		return 0;
	}

	/* death_by_timeout would report the event again */
	set_bit(IPS_DYING_BIT, &ct->status);

	nf_ct_kill(ct);
	nf_ct_put(ct);

	return 0;
}