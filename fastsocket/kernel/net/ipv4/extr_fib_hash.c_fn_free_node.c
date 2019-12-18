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
struct fib_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fn_hash_kmem ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fib_node*) ; 

__attribute__((used)) static inline void fn_free_node(struct fib_node * f)
{
	kmem_cache_free(fn_hash_kmem, f);
}