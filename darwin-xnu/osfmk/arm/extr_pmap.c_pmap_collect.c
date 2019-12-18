#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
struct TYPE_7__ {scalar_t__ nested; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_1__*) ; 
 TYPE_1__* PMAP_NULL ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_1__*) ; 
 TYPE_1__* kernel_pmap ; 

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