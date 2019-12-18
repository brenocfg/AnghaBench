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
struct TYPE_2__ {int /*<<< orphan*/  expect_vmalloc; int /*<<< orphan*/  expect_hash; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  exp_proc_remove (struct net*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_expect_cachep ; 
 int /*<<< orphan*/  nf_ct_expect_hsize ; 
 int /*<<< orphan*/  nf_ct_free_hashtable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier () ; 

void nf_conntrack_expect_fini(struct net *net)
{
	exp_proc_remove(net);
	if (net_eq(net, &init_net)) {
		rcu_barrier(); /* Wait for call_rcu() before destroy */
		kmem_cache_destroy(nf_ct_expect_cachep);
	}
	nf_ct_free_hashtable(net->ct.expect_hash, net->ct.expect_vmalloc,
			     nf_ct_expect_hsize);
}