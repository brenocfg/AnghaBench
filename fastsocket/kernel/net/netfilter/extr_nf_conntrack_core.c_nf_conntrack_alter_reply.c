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
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn_help {int /*<<< orphan*/  expectations; } ;
struct nf_conn {scalar_t__ master; TYPE_1__* tuplehash; } ;
struct TYPE_2__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t IP_CT_DIR_REPLY ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int) ; 
 int /*<<< orphan*/  __nf_ct_try_assign_helper (struct nf_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (struct nf_conntrack_tuple const*) ; 
 int /*<<< orphan*/  nf_ct_is_confirmed (struct nf_conn*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct nf_conn*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void nf_conntrack_alter_reply(struct nf_conn *ct,
			      const struct nf_conntrack_tuple *newreply)
{
	struct nf_conn_help *help = nfct_help(ct);

	/* Should be unconfirmed, so not in hash table yet */
	NF_CT_ASSERT(!nf_ct_is_confirmed(ct));

	pr_debug("Altering reply tuple of %p to ", ct);
	nf_ct_dump_tuple(newreply);

	ct->tuplehash[IP_CT_DIR_REPLY].tuple = *newreply;
	if (ct->master || (help && !hlist_empty(&help->expectations)))
		return;

	rcu_read_lock();
	__nf_ct_try_assign_helper(ct, GFP_ATOMIC);
	rcu_read_unlock();
}