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
struct memcg_batch_info {int bytes; int memsw_bytes; struct mem_cgroup* memcg; int /*<<< orphan*/  do_batch; } ;
struct mem_cgroup {int /*<<< orphan*/  memsw; int /*<<< orphan*/  res; } ;
typedef  enum charge_type { ____Placeholder_charge_type } charge_type ;
struct TYPE_2__ {struct memcg_batch_info memcg_batch; } ;

/* Variables and functions */
 int const MEM_CGROUP_CHARGE_TYPE_SWAPOUT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TIF_MEMDIE ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_swap_account ; 
 int /*<<< orphan*/  memcg_oom_recover (struct mem_cgroup*) ; 
 int /*<<< orphan*/  res_counter_uncharge (int /*<<< orphan*/ *,int) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
__do_uncharge(struct mem_cgroup *mem, const enum charge_type ctype, int page_size)
{
	struct memcg_batch_info *batch = NULL;
	bool uncharge_memsw = true;

	/* If swapout, usage of swap doesn't decrease */
	if (!do_swap_account || ctype == MEM_CGROUP_CHARGE_TYPE_SWAPOUT)
		uncharge_memsw = false;

	batch = &current->memcg_batch;
	/*
	 * In usual, we do css_get() when we remember memcg pointer.
	 * But in this case, we keep res->usage until end of a series of
	 * uncharges. Then, it's ok to ignore memcg's refcnt.
	 */
	if (!batch->memcg)
		batch->memcg = mem;
	/*
	 * do_batch > 0 when unmapping pages or inode invalidate/truncate.
	 * In those cases, all pages freed continously can be expected to be in
	 * the same cgroup and we have chance to coalesce uncharges.
	 * But we do uncharge one by one if this is killed by OOM(TIF_MEMDIE)
	 * because we want to do uncharge as soon as possible.
	 */

	if (!batch->do_batch || test_thread_flag(TIF_MEMDIE))
		goto direct_uncharge;

	if (page_size > PAGE_SIZE)
		goto direct_uncharge;

	/*
	 * In typical case, batch->memcg == mem. This means we can
	 * merge a series of uncharges to an uncharge of res_counter.
	 * If not, we uncharge res_counter ony by one.
	 */
	if (batch->memcg != mem)
		goto direct_uncharge;
	/* remember freed charge and uncharge it later */
	batch->bytes += page_size;
	if (uncharge_memsw)
		batch->memsw_bytes += page_size;
	return;
direct_uncharge:
	res_counter_uncharge(&mem->res, page_size);
	if (uncharge_memsw)
		res_counter_uncharge(&mem->memsw, page_size);
	if (unlikely(batch->memcg != mem))
		memcg_oom_recover(mem);
	return;
}