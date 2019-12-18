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
typedef  int uint64_t ;
struct blkio_group_stats_cpu {int sectors; int /*<<< orphan*/  syncp; int /*<<< orphan*/ * stat_arr_cpu; } ;
struct blkio_group {int /*<<< orphan*/  stats_cpu; } ;

/* Variables and functions */
 size_t BLKIO_STAT_CPU_SERVICED ; 
 size_t BLKIO_STAT_CPU_SERVICE_BYTES ; 
 int /*<<< orphan*/  blkio_add_stat (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct blkio_group_stats_cpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void blkiocg_update_dispatch_stats(struct blkio_group *blkg,
				uint64_t bytes, bool direction, bool sync)
{
	struct blkio_group_stats_cpu *stats_cpu;
	unsigned long flags;

	/*
	 * Disabling interrupts to provide mutual exclusion between two
	 * writes on same cpu. It probably is not needed for 64bit. Not
	 * optimizing that case yet.
	 */
	local_irq_save(flags);

	stats_cpu = this_cpu_ptr(blkg->stats_cpu);

	u64_stats_update_begin(&stats_cpu->syncp);
	stats_cpu->sectors += bytes >> 9;
	blkio_add_stat(stats_cpu->stat_arr_cpu[BLKIO_STAT_CPU_SERVICED],
			1, direction, sync);
	blkio_add_stat(stats_cpu->stat_arr_cpu[BLKIO_STAT_CPU_SERVICE_BYTES],
			bytes, direction, sync);
	u64_stats_update_end(&stats_cpu->syncp);
	local_irq_restore(flags);
}