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
struct pmb_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct pmb_entry*) ; 
 int /*<<< orphan*/  pmb_cache ; 
 int /*<<< orphan*/  pmb_list_del (struct pmb_entry*) ; 
 int /*<<< orphan*/  pmb_list_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void pmb_free(struct pmb_entry *pmbe)
{
	spin_lock_irq(&pmb_list_lock);
	pmb_list_del(pmbe);
	spin_unlock_irq(&pmb_list_lock);

	kmem_cache_free(pmb_cache, pmbe);
}