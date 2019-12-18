#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long bitcnt; int /*<<< orphan*/  count; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__ mm_tracking_struct ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned long,int /*<<< orphan*/ ) ; 

void do_mm_track_phys(void *val)
{
	unsigned long pfn;

	pfn = (unsigned long)val >> PAGE_SHIFT;

	if (pfn >= mm_tracking_struct.bitcnt)
		return;

	if (!test_and_set_bit(pfn, mm_tracking_struct.vector))
		atomic_inc(&mm_tracking_struct.count);
}