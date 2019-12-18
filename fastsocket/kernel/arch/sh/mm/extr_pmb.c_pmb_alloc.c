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
struct pmb_entry {unsigned long vpn; unsigned long ppn; unsigned long flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct pmb_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pmb_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmb_cache ; 
 int /*<<< orphan*/  pmb_list_add (struct pmb_entry*) ; 
 int /*<<< orphan*/  pmb_list_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

struct pmb_entry *pmb_alloc(unsigned long vpn, unsigned long ppn,
			    unsigned long flags)
{
	struct pmb_entry *pmbe;

	pmbe = kmem_cache_alloc(pmb_cache, GFP_KERNEL);
	if (!pmbe)
		return ERR_PTR(-ENOMEM);

	pmbe->vpn	= vpn;
	pmbe->ppn	= ppn;
	pmbe->flags	= flags;

	spin_lock_irq(&pmb_list_lock);
	pmb_list_add(pmbe);
	spin_unlock_irq(&pmb_list_lock);

	return pmbe;
}