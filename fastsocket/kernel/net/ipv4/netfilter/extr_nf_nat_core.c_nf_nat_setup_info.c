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
struct nf_nat_range {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn_nat {int /*<<< orphan*/  bysource; struct nf_conn* ct; } ;
struct nf_conn {int /*<<< orphan*/  status; TYPE_1__* tuplehash; } ;
struct TYPE_4__ {int /*<<< orphan*/ * nat_bysource; } ;
struct net {TYPE_2__ ipv4; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
struct TYPE_3__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPS_DST_NAT ; 
 int /*<<< orphan*/  IPS_DST_NAT_DONE_BIT ; 
 int /*<<< orphan*/  IPS_SRC_NAT ; 
 int /*<<< orphan*/  IPS_SRC_NAT_DONE_BIT ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 size_t IP_CT_DIR_REPLY ; 
 int IP_NAT_MANIP_DST ; 
 int IP_NAT_MANIP_SRC ; 
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int) ; 
 int /*<<< orphan*/  NF_CT_EXT_NAT ; 
 int /*<<< orphan*/  get_unique_tuple (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*,struct nf_nat_range const*,struct nf_conn*,int) ; 
 unsigned int hash_by_src (struct net*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_alter_reply (struct nf_conn*,struct nf_conntrack_tuple*) ; 
 struct nf_conn_nat* nf_ct_ext_add (struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_invert_tuplepr (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_tuple_equal (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_nat_initialized (struct nf_conn*,int) ; 
 int /*<<< orphan*/  nf_nat_lock ; 
 struct nf_conn_nat* nfct_nat (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

unsigned int
nf_nat_setup_info(struct nf_conn *ct,
		  const struct nf_nat_range *range,
		  enum nf_nat_manip_type maniptype)
{
	struct net *net = nf_ct_net(ct);
	struct nf_conntrack_tuple curr_tuple, new_tuple;
	struct nf_conn_nat *nat;

	/* nat helper or nfctnetlink also setup binding */
	nat = nfct_nat(ct);
	if (!nat) {
		nat = nf_ct_ext_add(ct, NF_CT_EXT_NAT, GFP_ATOMIC);
		if (nat == NULL) {
			pr_debug("failed to add NAT extension\n");
			return NF_ACCEPT;
		}
	}

	NF_CT_ASSERT(maniptype == IP_NAT_MANIP_SRC ||
		     maniptype == IP_NAT_MANIP_DST);
	BUG_ON(nf_nat_initialized(ct, maniptype));

	/* What we've got will look like inverse of reply. Normally
	   this is what is in the conntrack, except for prior
	   manipulations (future optimization: if num_manips == 0,
	   orig_tp =
	   conntrack->tuplehash[IP_CT_DIR_ORIGINAL].tuple) */
	nf_ct_invert_tuplepr(&curr_tuple,
			     &ct->tuplehash[IP_CT_DIR_REPLY].tuple);

	get_unique_tuple(&new_tuple, &curr_tuple, range, ct, maniptype);

	if (!nf_ct_tuple_equal(&new_tuple, &curr_tuple)) {
		struct nf_conntrack_tuple reply;

		/* Alter conntrack table so will recognize replies. */
		nf_ct_invert_tuplepr(&reply, &new_tuple);
		nf_conntrack_alter_reply(ct, &reply);

		/* Non-atomic: we own this at the moment. */
		if (maniptype == IP_NAT_MANIP_SRC)
			ct->status |= IPS_SRC_NAT;
		else
			ct->status |= IPS_DST_NAT;
	}

	if (maniptype == IP_NAT_MANIP_SRC) {
		unsigned int srchash;

		srchash = hash_by_src(net, &ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
		spin_lock_bh(&nf_nat_lock);
		/* nf_conntrack_alter_reply might re-allocate exntension aera */
		nat = nfct_nat(ct);
		nat->ct = ct;
		hlist_add_head_rcu(&nat->bysource,
				   &net->ipv4.nat_bysource[srchash]);
		spin_unlock_bh(&nf_nat_lock);
	}

	/* It's done. */
	if (maniptype == IP_NAT_MANIP_DST)
		set_bit(IPS_DST_NAT_DONE_BIT, &ct->status);
	else
		set_bit(IPS_SRC_NAT_DONE_BIT, &ct->status);

	return NF_ACCEPT;
}