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
struct nf_conntrack_l3proto {int /*<<< orphan*/  me; } ;

/* Variables and functions */
 struct nf_conntrack_l3proto* __nf_ct_l3proto_find (unsigned short) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void nf_ct_l3proto_module_put(unsigned short l3proto)
{
	struct nf_conntrack_l3proto *p;

	/* rcu_read_lock not necessary since the caller holds a reference */
	p = __nf_ct_l3proto_find(l3proto);
	module_put(p->me);
}