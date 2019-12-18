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
struct fib_alias {int /*<<< orphan*/ * fa_info; } ;
struct fib_node {struct fib_alias fn_embedded_alias; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib_release_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fn_alias_kmem ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fib_alias*) ; 

__attribute__((used)) static inline void fn_free_alias(struct fib_alias *fa, struct fib_node *f)
{
	fib_release_info(fa->fa_info);
	if (fa == &f->fn_embedded_alias)
		fa->fa_info = NULL;
	else
		kmem_cache_free(fn_alias_kmem, fa);
}