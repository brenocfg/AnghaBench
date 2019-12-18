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
typedef  int /*<<< orphan*/  u8 ;
struct rt6key {int /*<<< orphan*/  addr; } ;
struct in6_addr {int dummy; } ;
struct fib6_node {int fn_bit; struct fib6_node* left; struct fib6_node* right; scalar_t__ leaf; } ;

/* Variables and functions */
 scalar_t__ addr_bit_set (struct in6_addr*,int) ; 
 int /*<<< orphan*/  ipv6_prefix_equal (int /*<<< orphan*/ *,struct in6_addr*,int) ; 

__attribute__((used)) static struct fib6_node * fib6_locate_1(struct fib6_node *root,
					struct in6_addr *addr,
					int plen, int offset)
{
	struct fib6_node *fn;

	for (fn = root; fn ; ) {
		struct rt6key *key = (struct rt6key *)((u8 *)fn->leaf + offset);

		/*
		 *	Prefix match
		 */
		if (plen < fn->fn_bit ||
		    !ipv6_prefix_equal(&key->addr, addr, fn->fn_bit))
			return NULL;

		if (plen == fn->fn_bit)
			return fn;

		/*
		 *	We have more bits to go
		 */
		if (addr_bit_set(addr, fn->fn_bit))
			fn = fn->right;
		else
			fn = fn->left;
	}
	return NULL;
}