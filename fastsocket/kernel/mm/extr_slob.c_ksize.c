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
struct TYPE_2__ {size_t private; } ;
struct slob_page {TYPE_1__ page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_KMALLOC_MINALIGN ; 
 int /*<<< orphan*/  ARCH_SLAB_MINALIGN ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t SLOB_UNIT ; 
 size_t SLOB_UNITS (unsigned int) ; 
 void const* ZERO_SIZE_PTR ; 
 scalar_t__ is_slob_page (struct slob_page*) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct slob_page* slob_page (void const*) ; 
 scalar_t__ unlikely (int) ; 

size_t ksize(const void *block)
{
	struct slob_page *sp;

	BUG_ON(!block);
	if (unlikely(block == ZERO_SIZE_PTR))
		return 0;

	sp = slob_page(block);
	if (is_slob_page(sp)) {
		int align = max(ARCH_KMALLOC_MINALIGN, ARCH_SLAB_MINALIGN);
		unsigned int *m = (unsigned int *)(block - align);
		return SLOB_UNITS(*m) * SLOB_UNIT;
	} else
		return sp->page.private;
}