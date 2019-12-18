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
struct TYPE_2__ {scalar_t__ free_offset; } ;
struct smem_shared {TYPE_1__ heap_info; } ;

/* Variables and functions */
 scalar_t__ MSM_SHARED_RAM_BASE ; 
 scalar_t__ last_heap_free ; 
 int /*<<< orphan*/  probe_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_smd_probe(void)
{
	struct smem_shared *shared = (void *) MSM_SHARED_RAM_BASE;
	if (shared->heap_info.free_offset != last_heap_free) {
		last_heap_free = shared->heap_info.free_offset;
		schedule_work(&probe_work);
	}
}