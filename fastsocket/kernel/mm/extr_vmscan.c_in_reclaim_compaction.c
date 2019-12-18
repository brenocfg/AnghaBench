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
struct scan_control {scalar_t__ order; } ;

/* Variables and functions */
 scalar_t__ COMPACTION_BUILD ; 
 int DEF_PRIORITY ; 
 scalar_t__ PAGE_ALLOC_COSTLY_ORDER ; 

__attribute__((used)) static bool in_reclaim_compaction(int priority, struct scan_control *sc)
{
	if (COMPACTION_BUILD && sc->order &&
			(sc->order > PAGE_ALLOC_COSTLY_ORDER ||
			 priority < DEF_PRIORITY - 2))
		return true;

	return false;
}