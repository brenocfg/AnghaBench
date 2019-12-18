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
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (struct kmem_cache*) ; 

__attribute__((used)) static void
nfsd4_free_slab(struct kmem_cache **slab)
{
	if (*slab == NULL)
		return;
	kmem_cache_destroy(*slab);
	*slab = NULL;
}