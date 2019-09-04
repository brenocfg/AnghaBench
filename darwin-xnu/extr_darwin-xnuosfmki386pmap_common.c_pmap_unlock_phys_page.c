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
typedef  int /*<<< orphan*/  ppnum_t ;

/* Variables and functions */
 scalar_t__ IS_MANAGED_PAGE (int) ; 
 int /*<<< orphan*/  UNLOCK_PVH (int) ; 
 int /*<<< orphan*/  phys_backup_lock ; 
 int ppn_to_pai (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
pmap_unlock_phys_page(ppnum_t pn)
{
	int		pai;

	pai = ppn_to_pai(pn);

	if (IS_MANAGED_PAGE(pai)) {
		UNLOCK_PVH(pai);
	} else
		simple_unlock(&phys_backup_lock);
}