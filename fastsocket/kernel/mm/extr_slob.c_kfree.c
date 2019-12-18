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
struct slob_page {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_KMALLOC_MINALIGN ; 
 int /*<<< orphan*/  ARCH_SLAB_MINALIGN ; 
 int /*<<< orphan*/  ZERO_OR_NULL_PTR (void const*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 scalar_t__ is_slob_page (struct slob_page*) ; 
 int /*<<< orphan*/  kmemleak_free (void const*) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slob_free (unsigned int*,unsigned int) ; 
 struct slob_page* slob_page (void const*) ; 
 int /*<<< orphan*/  trace_kfree (int /*<<< orphan*/ ,void const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void kfree(const void *block)
{
	struct slob_page *sp;

	trace_kfree(_RET_IP_, block);

	if (unlikely(ZERO_OR_NULL_PTR(block)))
		return;
	kmemleak_free(block);

	sp = slob_page(block);
	if (is_slob_page(sp)) {
		int align = max(ARCH_KMALLOC_MINALIGN, ARCH_SLAB_MINALIGN);
		unsigned int *m = (unsigned int *)(block - align);
		slob_free(m, *m + align);
	} else
		put_page(&sp->page);
}