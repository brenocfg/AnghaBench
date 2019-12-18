#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  use; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_conntrack_expect* __nf_ct_expect_find (struct net*,struct nf_conntrack_tuple const*) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct nf_conntrack_expect *
nf_ct_expect_find_get(struct net *net, const struct nf_conntrack_tuple *tuple)
{
	struct nf_conntrack_expect *i;

	rcu_read_lock();
	i = __nf_ct_expect_find(net, tuple);
	if (i && !atomic_inc_not_zero(&i->use))
		i = NULL;
	rcu_read_unlock();

	return i;
}