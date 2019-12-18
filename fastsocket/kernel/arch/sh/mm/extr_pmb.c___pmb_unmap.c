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
struct pmb_entry {scalar_t__ entry; struct pmb_entry* link; } ;

/* Variables and functions */
 scalar_t__ PMB_NO_ENTRY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_pmb_entry (struct pmb_entry*) ; 
 int /*<<< orphan*/  pmb_free (struct pmb_entry*) ; 
 int /*<<< orphan*/  pmb_map ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __pmb_unmap(struct pmb_entry *pmbe)
{
	WARN_ON(!test_bit(pmbe->entry, &pmb_map));

	do {
		struct pmb_entry *pmblink = pmbe;

		if (pmbe->entry != PMB_NO_ENTRY)
			clear_pmb_entry(pmbe);

		pmbe = pmblink->link;

		pmb_free(pmblink);
	} while (pmbe);
}