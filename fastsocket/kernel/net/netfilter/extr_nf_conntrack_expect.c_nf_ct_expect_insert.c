#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nf_conntrack_expect_policy {int timeout; } ;
struct TYPE_7__ {scalar_t__ expires; } ;
struct nf_conntrack_expect {size_t class; int /*<<< orphan*/  use; TYPE_3__ timeout; int /*<<< orphan*/  hnode; int /*<<< orphan*/  lnode; int /*<<< orphan*/  tuple; int /*<<< orphan*/  master; } ;
struct nf_conn_help {TYPE_2__* helper; int /*<<< orphan*/ * expecting; int /*<<< orphan*/  expectations; } ;
struct TYPE_5__ {int /*<<< orphan*/  expect_count; int /*<<< orphan*/ * expect_hash; } ;
struct net {TYPE_1__ ct; } ;
struct TYPE_6__ {struct nf_conntrack_expect_policy* expect_policy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NF_CT_STAT_INC (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect_create ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 struct net* nf_ct_exp_net (struct nf_conntrack_expect*) ; 
 unsigned int nf_ct_expect_dst_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_expectation_timed_out ; 
 struct nf_conn_help* nfct_help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (TYPE_3__*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void nf_ct_expect_insert(struct nf_conntrack_expect *exp)
{
	struct nf_conn_help *master_help = nfct_help(exp->master);
	struct net *net = nf_ct_exp_net(exp);
	const struct nf_conntrack_expect_policy *p;
	unsigned int h = nf_ct_expect_dst_hash(&exp->tuple);

	atomic_inc(&exp->use);

	hlist_add_head(&exp->lnode, &master_help->expectations);
	master_help->expecting[exp->class]++;

	hlist_add_head_rcu(&exp->hnode, &net->ct.expect_hash[h]);
	net->ct.expect_count++;

	setup_timer(&exp->timeout, nf_ct_expectation_timed_out,
		    (unsigned long)exp);
	p = &master_help->helper->expect_policy[exp->class];
	exp->timeout.expires = jiffies + p->timeout * HZ;
	add_timer(&exp->timeout);

	atomic_inc(&exp->use);
	NF_CT_STAT_INC(net, expect_create);
}