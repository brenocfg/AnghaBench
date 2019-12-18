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
struct rt6_info {int dummy; } ;
struct net {int dummy; } ;
struct fib6_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_clean_tree (struct net*,struct fib6_node*,int /*<<< orphan*/ ,int,struct rt6_info*) ; 
 int /*<<< orphan*/  fib6_prune_clone ; 

__attribute__((used)) static void fib6_prune_clones(struct net *net, struct fib6_node *fn,
			      struct rt6_info *rt)
{
	fib6_clean_tree(net, fn, fib6_prune_clone, 1, rt);
}