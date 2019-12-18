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
struct nf_conn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nf_conntrack_cachep; int /*<<< orphan*/  count; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_ext_destroy (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_ext_free (struct nf_conn*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 

void nf_conntrack_free(struct nf_conn *ct)
{
	struct net *net = nf_ct_net(ct);

	nf_ct_ext_destroy(ct);
	atomic_dec(&net->ct.count);
	nf_ct_ext_free(ct);
	kmem_cache_free(net->ct.nf_conntrack_cachep, ct);
}