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
typedef  int /*<<< orphan*/  u8 ;
struct nlattr {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_helper {int dummy; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct TYPE_2__ {int expires; } ;
struct nf_conn {TYPE_1__ timeout; struct nf_conn* master; int /*<<< orphan*/  status; void* mark; } ;

/* Variables and functions */
 size_t CTA_HELP ; 
 size_t CTA_MARK ; 
 size_t CTA_NAT_DST ; 
 size_t CTA_NAT_SEQ_ADJ_ORIG ; 
 size_t CTA_NAT_SEQ_ADJ_REPLY ; 
 size_t CTA_NAT_SRC ; 
 size_t CTA_PROTOINFO ; 
 size_t CTA_STATUS ; 
 size_t CTA_TIMEOUT ; 
 size_t CTA_TUPLE_MASTER ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct nf_conn* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  IPS_CONFIRMED ; 
 int /*<<< orphan*/  IPS_EXPECTED_BIT ; 
 scalar_t__ IS_ERR (struct nf_conn*) ; 
 struct nf_conntrack_helper* __nf_conntrack_helper_find_byname (char*) ; 
 int __nf_ct_try_assign_helper (struct nf_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int ctnetlink_change_nat (struct nf_conn*,struct nlattr const* const*) ; 
 int ctnetlink_change_nat_seq_adj (struct nf_conn*,struct nlattr const* const*) ; 
 int ctnetlink_change_protoinfo (struct nf_conn*,struct nlattr const* const*) ; 
 int ctnetlink_change_status (struct nf_conn*,struct nlattr const* const*) ; 
 int ctnetlink_parse_help (struct nlattr const* const,char**) ; 
 int ctnetlink_parse_tuple (struct nlattr const* const*,struct nf_conntrack_tuple*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int jiffies ; 
 struct nf_conn* nf_conntrack_alloc (int /*<<< orphan*/ *,struct nf_conntrack_tuple*,struct nf_conntrack_tuple*,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (int /*<<< orphan*/ *,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_conntrack_free (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_conntrack_hash_insert (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_acct_ext_add (struct nf_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_ecache_ext_add (struct nf_conn*,int /*<<< orphan*/ ) ; 
 struct nf_conn_help* nf_ct_helper_ext_add (struct nf_conn*,int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_conntrack_helper*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ request_module (char*,char*) ; 

__attribute__((used)) static struct nf_conn *
ctnetlink_create_conntrack(const struct nlattr * const cda[],
			   struct nf_conntrack_tuple *otuple,
			   struct nf_conntrack_tuple *rtuple,
			   u8 u3)
{
	struct nf_conn *ct;
	int err = -EINVAL;
	struct nf_conntrack_helper *helper;

	ct = nf_conntrack_alloc(&init_net, otuple, rtuple, GFP_ATOMIC);
	if (IS_ERR(ct))
		return ERR_PTR(-ENOMEM);

	if (!cda[CTA_TIMEOUT])
		goto err1;
	ct->timeout.expires = ntohl(nla_get_be32(cda[CTA_TIMEOUT]));

	ct->timeout.expires = jiffies + ct->timeout.expires * HZ;
	ct->status |= IPS_CONFIRMED;

	rcu_read_lock();
 	if (cda[CTA_HELP]) {
		char *helpname = NULL;
 
 		err = ctnetlink_parse_help(cda[CTA_HELP], &helpname);
 		if (err < 0)
			goto err2;

		helper = __nf_conntrack_helper_find_byname(helpname);
		if (helper == NULL) {
			rcu_read_unlock();
#ifdef CONFIG_MODULES
			if (request_module("nfct-helper-%s", helpname) < 0) {
				err = -EOPNOTSUPP;
				goto err1;
			}

			rcu_read_lock();
			helper = __nf_conntrack_helper_find_byname(helpname);
			if (helper) {
				err = -EAGAIN;
				goto err2;
			}
			rcu_read_unlock();
#endif
			err = -EOPNOTSUPP;
			goto err1;
		} else {
			struct nf_conn_help *help;

			help = nf_ct_helper_ext_add(ct, GFP_ATOMIC);
			if (help == NULL) {
				err = -ENOMEM;
				goto err2;
			}

			/* not in hash table yet so not strictly necessary */
			rcu_assign_pointer(help->helper, helper);
		}
	} else {
		/* try an implicit helper assignation */
		err = __nf_ct_try_assign_helper(ct, GFP_ATOMIC);
		if (err < 0)
			goto err2;
	}

	if (cda[CTA_STATUS]) {
		err = ctnetlink_change_status(ct, cda);
		if (err < 0)
			goto err2;
	}

	if (cda[CTA_NAT_SRC] || cda[CTA_NAT_DST]) {
		err = ctnetlink_change_nat(ct, cda);
		if (err < 0)
			goto err2;
	}

#ifdef CONFIG_NF_NAT_NEEDED
	if (cda[CTA_NAT_SEQ_ADJ_ORIG] || cda[CTA_NAT_SEQ_ADJ_REPLY]) {
		err = ctnetlink_change_nat_seq_adj(ct, cda);
		if (err < 0)
			goto err2;
	}
#endif

	if (cda[CTA_PROTOINFO]) {
		err = ctnetlink_change_protoinfo(ct, cda);
		if (err < 0)
			goto err2;
	}

	nf_ct_acct_ext_add(ct, GFP_ATOMIC);
	nf_ct_ecache_ext_add(ct, GFP_ATOMIC);

#if defined(CONFIG_NF_CONNTRACK_MARK)
	if (cda[CTA_MARK])
		ct->mark = ntohl(nla_get_be32(cda[CTA_MARK]));
#endif

	/* setup master conntrack: this is a confirmed expectation */
	if (cda[CTA_TUPLE_MASTER]) {
		struct nf_conntrack_tuple master;
		struct nf_conntrack_tuple_hash *master_h;
		struct nf_conn *master_ct;

		err = ctnetlink_parse_tuple(cda, &master, CTA_TUPLE_MASTER, u3);
		if (err < 0)
			goto err2;

		master_h = nf_conntrack_find_get(&init_net, &master);
		if (master_h == NULL) {
			err = -ENOENT;
			goto err2;
		}
		master_ct = nf_ct_tuplehash_to_ctrack(master_h);
		__set_bit(IPS_EXPECTED_BIT, &ct->status);
		ct->master = master_ct;
	}

	add_timer(&ct->timeout);
	nf_conntrack_hash_insert(ct);
	rcu_read_unlock();

	return ct;

err2:
	rcu_read_unlock();
err1:
	nf_conntrack_free(ct);
	return ERR_PTR(err);
}