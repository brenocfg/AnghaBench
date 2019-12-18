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
struct seq_file {struct ct_expect_iter_state* private; } ;
struct TYPE_4__ {TYPE_1__* expect_hash; } ;
struct net {TYPE_2__ ct; } ;
struct hlist_node {int dummy; } ;
struct ct_expect_iter_state {size_t bucket; } ;
struct TYPE_3__ {int /*<<< orphan*/  first; } ;

/* Variables and functions */
 size_t nf_ct_expect_hsize ; 
 struct hlist_node* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct net* seq_file_net (struct seq_file*) ; 

__attribute__((used)) static struct hlist_node *ct_expect_get_first(struct seq_file *seq)
{
	struct net *net = seq_file_net(seq);
	struct ct_expect_iter_state *st = seq->private;
	struct hlist_node *n;

	for (st->bucket = 0; st->bucket < nf_ct_expect_hsize; st->bucket++) {
		n = rcu_dereference(net->ct.expect_hash[st->bucket].first);
		if (n)
			return n;
	}
	return NULL;
}