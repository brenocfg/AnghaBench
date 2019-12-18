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
typedef  int /*<<< orphan*/  pmap_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNLOCK_PVH (int) ; 
 scalar_t__ pa_index (int /*<<< orphan*/ ) ; 
 scalar_t__ pa_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_backup_lock ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
pmap_unlock_phys_page(ppnum_t pn)
{
	int             pai;
	pmap_paddr_t	phys = ptoa(pn);

	if (pa_valid(phys)) {
		pai = (int)pa_index(phys);
		UNLOCK_PVH(pai);
	} else
	simple_unlock(&phys_backup_lock);
}