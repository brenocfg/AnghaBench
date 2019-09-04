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
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 scalar_t__ PMAP_NULL ; 

void
pmap_collect(pmap_t pmap)
{
	if (pmap == PMAP_NULL)
		return;

#if 0
	PMAP_LOCK(pmap);
	if ((pmap->nested == FALSE) && (pmap != kernel_pmap)) {
		/* TODO: Scan for vm page assigned to top level page tables with no reference */
	}
	PMAP_UNLOCK(pmap);
#endif

	return;
}