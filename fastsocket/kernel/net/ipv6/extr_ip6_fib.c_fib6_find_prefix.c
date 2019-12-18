#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rt6_info {int dummy; } ;
struct TYPE_4__ {struct rt6_info* ip6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_node {int fn_flags; TYPE_3__* right; TYPE_2__* left; } ;
struct TYPE_6__ {struct rt6_info* leaf; } ;
struct TYPE_5__ {struct rt6_info* leaf; } ;

/* Variables and functions */
 struct fib6_node* FIB6_SUBTREE (struct fib6_node*) ; 
 int RTN_ROOT ; 

__attribute__((used)) static struct rt6_info *fib6_find_prefix(struct net *net, struct fib6_node *fn)
{
	if (fn->fn_flags&RTN_ROOT)
		return net->ipv6.ip6_null_entry;

	while(fn) {
		if(fn->left)
			return fn->left->leaf;

		if(fn->right)
			return fn->right->leaf;

		fn = FIB6_SUBTREE(fn);
	}
	return NULL;
}