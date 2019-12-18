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
struct TYPE_2__ {unsigned int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int PF_MEMALLOC ; 
 TYPE_1__* current ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *alloc_pgtable_page(void)
{
	unsigned int flags;
	void *vaddr;

	/* trying to avoid low memory issues */
	flags = current->flags & PF_MEMALLOC;
	current->flags |= PF_MEMALLOC;
	vaddr = (void *)get_zeroed_page(GFP_ATOMIC);
	current->flags &= (~PF_MEMALLOC | flags);
	return vaddr;
}