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
struct kmmio_probe {unsigned long len; unsigned long addr; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EEXIST ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ add_kmmio_fault_page (unsigned long) ; 
 scalar_t__ get_kmmio_probe (unsigned long) ; 
 int /*<<< orphan*/  kmmio_count ; 
 int /*<<< orphan*/  kmmio_lock ; 
 int /*<<< orphan*/  kmmio_probes ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int register_kmmio_probe(struct kmmio_probe *p)
{
	unsigned long flags;
	int ret = 0;
	unsigned long size = 0;
	const unsigned long size_lim = p->len + (p->addr & ~PAGE_MASK);

	spin_lock_irqsave(&kmmio_lock, flags);
	if (get_kmmio_probe(p->addr)) {
		ret = -EEXIST;
		goto out;
	}
	kmmio_count++;
	list_add_rcu(&p->list, &kmmio_probes);
	while (size < size_lim) {
		if (add_kmmio_fault_page(p->addr + size))
			pr_err("kmmio: Unable to set page fault.\n");
		size += PAGE_SIZE;
	}
out:
	spin_unlock_irqrestore(&kmmio_lock, flags);
	/*
	 * XXX: What should I do here?
	 * Here was a call to global_flush_tlb(), but it does not exist
	 * anymore. It seems it's not needed after all.
	 */
	return ret;
}