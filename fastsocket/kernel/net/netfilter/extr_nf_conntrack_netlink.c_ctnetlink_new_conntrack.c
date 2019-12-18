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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  ct_general; int /*<<< orphan*/  status; } ;
typedef  enum ip_conntrack_events { ____Placeholder_ip_conntrack_events } ip_conntrack_events ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 size_t CTA_TUPLE_ORIG ; 
 size_t CTA_TUPLE_REPLY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int IPCT_HELPER ; 
 int IPCT_MARK ; 
 int IPCT_NATSEQADJ ; 
 int IPCT_NEW ; 
 int IPCT_PROTOINFO ; 
 int IPCT_RELATED ; 
 int IPCT_STATUS ; 
 int /*<<< orphan*/  IPS_EXPECTED_BIT ; 
 scalar_t__ IS_ERR (struct nf_conn*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int PTR_ERR (struct nf_conn*) ; 
 struct nf_conntrack_tuple_hash* __nf_conntrack_find (int /*<<< orphan*/ *,struct nf_conntrack_tuple*) ; 
 int ctnetlink_change_conntrack (struct nf_conn*,struct nlattr const* const*) ; 
 struct nf_conn* ctnetlink_create_conntrack (struct nlattr const* const*,struct nf_conntrack_tuple*,struct nf_conntrack_tuple*,int /*<<< orphan*/ ) ; 
 int ctnetlink_parse_tuple (struct nlattr const* const*,struct nf_conntrack_tuple*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  nf_conntrack_eventmask_report (int,struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_lock ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  nlmsg_report (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctnetlink_new_conntrack(struct sock *ctnl, struct sk_buff *skb,
			const struct nlmsghdr *nlh,
			const struct nlattr * const cda[])
{
	struct nf_conntrack_tuple otuple, rtuple;
	struct nf_conntrack_tuple_hash *h = NULL;
	struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u_int8_t u3 = nfmsg->nfgen_family;
	int err = 0;

	if (cda[CTA_TUPLE_ORIG]) {
		err = ctnetlink_parse_tuple(cda, &otuple, CTA_TUPLE_ORIG, u3);
		if (err < 0)
			return err;
	}

	if (cda[CTA_TUPLE_REPLY]) {
		err = ctnetlink_parse_tuple(cda, &rtuple, CTA_TUPLE_REPLY, u3);
		if (err < 0)
			return err;
	}

	spin_lock_bh(&nf_conntrack_lock);
	if (cda[CTA_TUPLE_ORIG])
		h = __nf_conntrack_find(&init_net, &otuple);
	else if (cda[CTA_TUPLE_REPLY])
		h = __nf_conntrack_find(&init_net, &rtuple);

	if (h == NULL) {
		err = -ENOENT;
		if (nlh->nlmsg_flags & NLM_F_CREATE) {
			struct nf_conn *ct;
			enum ip_conntrack_events events;

			if (!cda[CTA_TUPLE_ORIG] || !cda[CTA_TUPLE_REPLY]) {
				err = -EINVAL;
				goto out_unlock;
			}

			ct = ctnetlink_create_conntrack(cda, &otuple,
							&rtuple, u3);
			if (IS_ERR(ct)) {
				err = PTR_ERR(ct);
				goto out_unlock;
			}
			err = 0;
			nf_conntrack_get(&ct->ct_general);
			spin_unlock_bh(&nf_conntrack_lock);
			if (test_bit(IPS_EXPECTED_BIT, &ct->status))
				events = IPCT_RELATED;
			else
				events = IPCT_NEW;

			nf_conntrack_eventmask_report((1 << IPCT_STATUS) |
						      (1 << IPCT_HELPER) |
						      (1 << IPCT_PROTOINFO) |
						      (1 << IPCT_NATSEQADJ) |
						      (1 << IPCT_MARK) | events,
						      ct, NETLINK_CB(skb).pid,
						      nlmsg_report(nlh));
			nf_ct_put(ct);
		} else
			spin_unlock_bh(&nf_conntrack_lock);

		return err;
	}
	/* implicit 'else' */

	/* We manipulate the conntrack inside the global conntrack table lock,
	 * so there's no need to increase the refcount */
	err = -EEXIST;
	if (!(nlh->nlmsg_flags & NLM_F_EXCL)) {
		struct nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);

		err = ctnetlink_change_conntrack(ct, cda);
		if (err == 0) {
			nf_conntrack_get(&ct->ct_general);
			spin_unlock_bh(&nf_conntrack_lock);
			nf_conntrack_eventmask_report((1 << IPCT_STATUS) |
						      (1 << IPCT_HELPER) |
						      (1 << IPCT_PROTOINFO) |
						      (1 << IPCT_NATSEQADJ) |
						      (1 << IPCT_MARK),
						      ct, NETLINK_CB(skb).pid,
						      nlmsg_report(nlh));
			nf_ct_put(ct);
		} else
			spin_unlock_bh(&nf_conntrack_lock);

		return err;
	}

out_unlock:
	spin_unlock_bh(&nf_conntrack_lock);
	return err;
}