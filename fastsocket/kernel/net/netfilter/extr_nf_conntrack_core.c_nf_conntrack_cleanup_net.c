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
struct TYPE_2__ {int /*<<< orphan*/  stat; int /*<<< orphan*/  slabname; int /*<<< orphan*/  nf_conntrack_cachep; int /*<<< orphan*/  htable_size; int /*<<< orphan*/  hash_vmalloc; int /*<<< orphan*/  hash; int /*<<< orphan*/  count; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_all ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_acct_fini (struct net*) ; 
 int /*<<< orphan*/  nf_conntrack_ecache_fini (struct net*) ; 
 int /*<<< orphan*/  nf_conntrack_expect_fini (struct net*) ; 
 int /*<<< orphan*/  nf_ct_free_hashtable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_iterate_cleanup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_release_dying_list (struct net*) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void nf_conntrack_cleanup_net(struct net *net)
{
 i_see_dead_people:
	nf_ct_iterate_cleanup(net, kill_all, NULL);
	nf_ct_release_dying_list(net);
	if (atomic_read(&net->ct.count) != 0) {
		schedule();
		goto i_see_dead_people;
	}

	nf_ct_free_hashtable(net->ct.hash, net->ct.hash_vmalloc,
			     net->ct.htable_size);
	nf_conntrack_ecache_fini(net);
	nf_conntrack_acct_fini(net);
	nf_conntrack_expect_fini(net);
	kmem_cache_destroy(net->ct.nf_conntrack_cachep);
	kfree(net->ct.slabname);
	free_percpu(net->ct.stat);
}