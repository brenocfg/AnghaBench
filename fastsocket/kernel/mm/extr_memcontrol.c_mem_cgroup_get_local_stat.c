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
struct mem_cgroup {int /*<<< orphan*/  stat; } ;
struct mcs_total_stat {int* stat; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  LRU_ACTIVE_ANON ; 
 int /*<<< orphan*/  LRU_ACTIVE_FILE ; 
 int /*<<< orphan*/  LRU_INACTIVE_ANON ; 
 int /*<<< orphan*/  LRU_INACTIVE_FILE ; 
 int /*<<< orphan*/  LRU_UNEVICTABLE ; 
 size_t MCS_ACTIVE_ANON ; 
 size_t MCS_ACTIVE_FILE ; 
 size_t MCS_CACHE ; 
 size_t MCS_FILE_MAPPED ; 
 size_t MCS_INACTIVE_ANON ; 
 size_t MCS_INACTIVE_FILE ; 
 size_t MCS_PGPGIN ; 
 size_t MCS_PGPGOUT ; 
 size_t MCS_RSS ; 
 size_t MCS_SWAP ; 
 size_t MCS_UNEVICTABLE ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_CACHE ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_FILE_MAPPED ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_PGPGIN_COUNT ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_PGPGOUT_COUNT ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_RSS ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_SWAPOUT ; 
 int PAGE_SIZE ; 
 scalar_t__ do_swap_account ; 
 int mem_cgroup_get_local_zonestat (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 int mem_cgroup_read_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mem_cgroup_get_local_stat(struct mem_cgroup *mem, struct mcs_total_stat *s)
{
	s64 val;

	/* per cpu stat */
	val = mem_cgroup_read_stat(&mem->stat, MEM_CGROUP_STAT_CACHE);
	s->stat[MCS_CACHE] += val * PAGE_SIZE;
	val = mem_cgroup_read_stat(&mem->stat, MEM_CGROUP_STAT_RSS);
	s->stat[MCS_RSS] += val * PAGE_SIZE;
	val = mem_cgroup_read_stat(&mem->stat, MEM_CGROUP_STAT_FILE_MAPPED);
	s->stat[MCS_FILE_MAPPED] += val * PAGE_SIZE;
	val = mem_cgroup_read_stat(&mem->stat, MEM_CGROUP_STAT_PGPGIN_COUNT);
	s->stat[MCS_PGPGIN] += val;
	val = mem_cgroup_read_stat(&mem->stat, MEM_CGROUP_STAT_PGPGOUT_COUNT);
	s->stat[MCS_PGPGOUT] += val;
	if (do_swap_account) {
		val = mem_cgroup_read_stat(&mem->stat, MEM_CGROUP_STAT_SWAPOUT);
		s->stat[MCS_SWAP] += val * PAGE_SIZE;
	}

	/* per zone stat */
	val = mem_cgroup_get_local_zonestat(mem, LRU_INACTIVE_ANON);
	s->stat[MCS_INACTIVE_ANON] += val * PAGE_SIZE;
	val = mem_cgroup_get_local_zonestat(mem, LRU_ACTIVE_ANON);
	s->stat[MCS_ACTIVE_ANON] += val * PAGE_SIZE;
	val = mem_cgroup_get_local_zonestat(mem, LRU_INACTIVE_FILE);
	s->stat[MCS_INACTIVE_FILE] += val * PAGE_SIZE;
	val = mem_cgroup_get_local_zonestat(mem, LRU_ACTIVE_FILE);
	s->stat[MCS_ACTIVE_FILE] += val * PAGE_SIZE;
	val = mem_cgroup_get_local_zonestat(mem, LRU_UNEVICTABLE);
	s->stat[MCS_UNEVICTABLE] += val * PAGE_SIZE;
}