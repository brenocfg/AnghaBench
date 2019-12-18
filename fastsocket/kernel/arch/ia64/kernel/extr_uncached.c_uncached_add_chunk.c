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
struct uncached_pool {int nchunks_added; int /*<<< orphan*/  add_chunk_mutex; int /*<<< orphan*/  pool; int /*<<< orphan*/  status; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageUncached (struct page*) ; 
 int GFP_KERNEL ; 
 int GFP_THISNODE ; 
 scalar_t__ IA64_GRANULE_SHIFT ; 
 int IA64_GRANULE_SIZE ; 
 int MAX_CONVERTED_CHUNKS_PER_NODE ; 
 unsigned long PAGE_OFFSET ; 
 scalar_t__ PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PAL_STATUS_SUCCESS ; 
 int PAL_VISIBILITY_OK ; 
 int PAL_VISIBILITY_OK_REMOTE_NEEDED ; 
 int /*<<< orphan*/  PAL_VISIBILITY_PHYSICAL ; 
 int /*<<< orphan*/  SetPageUncached (struct page*) ; 
 int __GFP_ZERO ; 
 unsigned long __IA64_UNCACHED_OFFSET ; 
 struct page* alloc_pages_exact_node (int,int,scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,scalar_t__) ; 
 int gen_pool_add (int /*<<< orphan*/ ,unsigned long,int,int) ; 
 int ia64_pal_mc_drain () ; 
 int ia64_pal_prefetch_visibility (int /*<<< orphan*/ ) ; 
 scalar_t__ ia64_platform_is (char*) ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int smp_call_function (int /*<<< orphan*/ ,struct uncached_pool*,int) ; 
 int /*<<< orphan*/  sn_flush_all_caches (unsigned long,int) ; 
 int /*<<< orphan*/  uncached_ipi_mc_drain ; 
 int /*<<< orphan*/  uncached_ipi_visibility ; 

__attribute__((used)) static int uncached_add_chunk(struct uncached_pool *uc_pool, int nid)
{
	struct page *page;
	int status, i, nchunks_added = uc_pool->nchunks_added;
	unsigned long c_addr, uc_addr;

	if (mutex_lock_interruptible(&uc_pool->add_chunk_mutex) != 0)
		return -1;	/* interrupted by a signal */

	if (uc_pool->nchunks_added > nchunks_added) {
		/* someone added a new chunk while we were waiting */
		mutex_unlock(&uc_pool->add_chunk_mutex);
		return 0;
	}

	if (uc_pool->nchunks_added >= MAX_CONVERTED_CHUNKS_PER_NODE) {
		mutex_unlock(&uc_pool->add_chunk_mutex);
		return -1;
	}

	/* attempt to allocate a granule's worth of cached memory pages */

	page = alloc_pages_exact_node(nid,
				GFP_KERNEL | __GFP_ZERO | GFP_THISNODE,
				IA64_GRANULE_SHIFT-PAGE_SHIFT);
	if (!page) {
		mutex_unlock(&uc_pool->add_chunk_mutex);
		return -1;
	}

	/* convert the memory pages from cached to uncached */

	c_addr = (unsigned long)page_address(page);
	uc_addr = c_addr - PAGE_OFFSET + __IA64_UNCACHED_OFFSET;

	/*
	 * There's a small race here where it's possible for someone to
	 * access the page through /dev/mem halfway through the conversion
	 * to uncached - not sure it's really worth bothering about
	 */
	for (i = 0; i < (IA64_GRANULE_SIZE / PAGE_SIZE); i++)
		SetPageUncached(&page[i]);

	flush_tlb_kernel_range(uc_addr, uc_addr + IA64_GRANULE_SIZE);

	status = ia64_pal_prefetch_visibility(PAL_VISIBILITY_PHYSICAL);
	if (status == PAL_VISIBILITY_OK_REMOTE_NEEDED) {
		atomic_set(&uc_pool->status, 0);
		status = smp_call_function(uncached_ipi_visibility, uc_pool, 1);
		if (status || atomic_read(&uc_pool->status))
			goto failed;
	} else if (status != PAL_VISIBILITY_OK)
		goto failed;

	preempt_disable();

	if (ia64_platform_is("sn2"))
		sn_flush_all_caches(uc_addr, IA64_GRANULE_SIZE);
	else
		flush_icache_range(uc_addr, uc_addr + IA64_GRANULE_SIZE);

	/* flush the just introduced uncached translation from the TLB */
	local_flush_tlb_all();

	preempt_enable();

	status = ia64_pal_mc_drain();
	if (status != PAL_STATUS_SUCCESS)
		goto failed;
	atomic_set(&uc_pool->status, 0);
	status = smp_call_function(uncached_ipi_mc_drain, uc_pool, 1);
	if (status || atomic_read(&uc_pool->status))
		goto failed;

	/*
	 * The chunk of memory pages has been converted to uncached so now we
	 * can add it to the pool.
	 */
	status = gen_pool_add(uc_pool->pool, uc_addr, IA64_GRANULE_SIZE, nid);
	if (status)
		goto failed;

	uc_pool->nchunks_added++;
	mutex_unlock(&uc_pool->add_chunk_mutex);
	return 0;

	/* failed to convert or add the chunk so give it back to the kernel */
failed:
	for (i = 0; i < (IA64_GRANULE_SIZE / PAGE_SIZE); i++)
		ClearPageUncached(&page[i]);

	free_pages(c_addr, IA64_GRANULE_SHIFT-PAGE_SHIFT);
	mutex_unlock(&uc_pool->add_chunk_mutex);
	return -1;
}