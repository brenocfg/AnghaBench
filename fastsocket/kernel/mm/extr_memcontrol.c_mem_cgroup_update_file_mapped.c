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
struct page_cgroup {struct mem_cgroup* mem_cgroup; } ;
struct page {int dummy; } ;
struct mem_cgroup_stat_cpu {int dummy; } ;
struct mem_cgroup_stat {struct mem_cgroup_stat_cpu* cpustat; } ;
struct mem_cgroup {struct mem_cgroup_stat stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageCgroupFileMapped (struct page_cgroup*) ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_FILE_MAPPED ; 
 int /*<<< orphan*/  PageCgroupUsed (struct page_cgroup*) ; 
 int /*<<< orphan*/  SetPageCgroupFileMapped (struct page_cgroup*) ; 
 int /*<<< orphan*/  __mem_cgroup_stat_add_safe (struct mem_cgroup_stat_cpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_page_cgroup (struct page_cgroup*) ; 
 struct page_cgroup* lookup_page_cgroup (struct page*) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page_cgroup (struct page_cgroup*) ; 

void mem_cgroup_update_file_mapped(struct page *page, int val)
{
	struct mem_cgroup *mem;
	struct mem_cgroup_stat *stat;
	struct mem_cgroup_stat_cpu *cpustat;
	int cpu;
	struct page_cgroup *pc;

	pc = lookup_page_cgroup(page);
	if (unlikely(!pc))
		return;

	lock_page_cgroup(pc);
	mem = pc->mem_cgroup;
	if (!mem)
		goto done;

	if (!PageCgroupUsed(pc))
		goto done;

	/*
	 * Preemption is already disabled, we don't need get_cpu()
	 */
	cpu = smp_processor_id();
	stat = &mem->stat;
	cpustat = &stat->cpustat[cpu];

	__mem_cgroup_stat_add_safe(cpustat, MEM_CGROUP_STAT_FILE_MAPPED, val);
	if (val > 0)
		SetPageCgroupFileMapped(pc);
	else if (!page_mapped(page)) /* page could have been remapped */
		ClearPageCgroupFileMapped(pc);
done:
	unlock_page_cgroup(pc);
}