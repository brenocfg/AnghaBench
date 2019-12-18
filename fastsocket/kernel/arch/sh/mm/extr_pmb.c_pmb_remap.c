#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmb_entry {struct pmb_entry* link; } ;
struct TYPE_3__ {unsigned long size; int flag; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 long EBUSY ; 
 scalar_t__ IS_ERR (struct pmb_entry*) ; 
 int PMB_C ; 
 int PMB_UB ; 
 int PMB_WT ; 
 long PTR_ERR (struct pmb_entry*) ; 
 unsigned long _PAGE_CACHABLE ; 
 unsigned long _PAGE_WT ; 
 int /*<<< orphan*/  __pmb_unmap (struct pmb_entry*) ; 
 scalar_t__ likely (struct pmb_entry*) ; 
 struct pmb_entry* pmb_alloc (unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  pmb_free (struct pmb_entry*) ; 
 TYPE_1__* pmb_sizes ; 
 int set_pmb_entry (struct pmb_entry*) ; 

long pmb_remap(unsigned long vaddr, unsigned long phys,
	       unsigned long size, unsigned long flags)
{
	struct pmb_entry *pmbp, *pmbe;
	unsigned long wanted;
	int pmb_flags, i;
	long err;

	/* Convert typical pgprot value to the PMB equivalent */
	if (flags & _PAGE_CACHABLE) {
		if (flags & _PAGE_WT)
			pmb_flags = PMB_WT;
		else
			pmb_flags = PMB_C;
	} else
		pmb_flags = PMB_WT | PMB_UB;

	pmbp = NULL;
	wanted = size;

again:
	for (i = 0; i < ARRAY_SIZE(pmb_sizes); i++) {
		int ret;

		if (size < pmb_sizes[i].size)
			continue;

		pmbe = pmb_alloc(vaddr, phys, pmb_flags | pmb_sizes[i].flag);
		if (IS_ERR(pmbe)) {
			err = PTR_ERR(pmbe);
			goto out;
		}

		ret = set_pmb_entry(pmbe);
		if (ret != 0) {
			pmb_free(pmbe);
			err = -EBUSY;
			goto out;
		}

		phys	+= pmb_sizes[i].size;
		vaddr	+= pmb_sizes[i].size;
		size	-= pmb_sizes[i].size;

		/*
		 * Link adjacent entries that span multiple PMB entries
		 * for easier tear-down.
		 */
		if (likely(pmbp))
			pmbp->link = pmbe;

		pmbp = pmbe;

		/*
		 * Instead of trying smaller sizes on every iteration
		 * (even if we succeed in allocating space), try using
		 * pmb_sizes[i].size again.
		 */
		i--;
	}

	if (size >= 0x1000000)
		goto again;

	return wanted - size;

out:
	if (pmbp)
		__pmb_unmap(pmbp);

	return err;
}