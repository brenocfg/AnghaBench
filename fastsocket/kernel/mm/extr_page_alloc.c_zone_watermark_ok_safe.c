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
struct zone {long percpu_drift_mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 int __zone_watermark_ok (struct zone*,int,unsigned long,int,int,long) ; 
 long zone_page_state (struct zone*,int /*<<< orphan*/ ) ; 
 long zone_page_state_snapshot (struct zone*,int /*<<< orphan*/ ) ; 

bool zone_watermark_ok_safe(struct zone *z, int order, unsigned long mark,
		      int classzone_idx, int alloc_flags)
{
	long free_pages = zone_page_state(z, NR_FREE_PAGES);

	if (z->percpu_drift_mark && free_pages < z->percpu_drift_mark)
		free_pages = zone_page_state_snapshot(z, NR_FREE_PAGES);

	return __zone_watermark_ok(z, order, mark, classzone_idx, alloc_flags,
								free_pages);
}