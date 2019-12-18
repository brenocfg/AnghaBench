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
typedef  union task_union {int dummy; } task_union ;
struct thread_info {int dummy; } ;

/* Variables and functions */
 unsigned long BUCKET_ADDR (int) ; 
 union task_union* BUCKET_EMPTY ; 
 int /*<<< orphan*/  BUCKET_PTE (unsigned long) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NR_TASK_BUCKETS ; 
 unsigned long PAGE_SIZE ; 
 unsigned long THREAD_INFO_ORDER ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  get_locked_segment (unsigned long) ; 
 scalar_t__ invalid_segment ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 
 union task_union** sun4c_bucket ; 
 int /*<<< orphan*/  sun4c_flush_page (unsigned long) ; 
 scalar_t__ sun4c_get_segmap (unsigned long) ; 
 int sun4c_lowbucket_avail ; 
 int /*<<< orphan*/  sun4c_put_pte (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct thread_info *sun4c_alloc_thread_info(void)
{
	unsigned long addr, pages;
	int entry;

	pages = __get_free_pages(GFP_KERNEL, THREAD_INFO_ORDER);
	if (!pages)
		return NULL;

	for (entry = sun4c_lowbucket_avail; entry < NR_TASK_BUCKETS; entry++)
		if (sun4c_bucket[entry] == BUCKET_EMPTY)
			break;
	if (entry == NR_TASK_BUCKETS) {
		free_pages(pages, THREAD_INFO_ORDER);
		return NULL;
	}
	if (entry >= sun4c_lowbucket_avail)
		sun4c_lowbucket_avail = entry + 1;

	addr = BUCKET_ADDR(entry);
	sun4c_bucket[entry] = (union task_union *) addr;
	if(sun4c_get_segmap(addr) == invalid_segment)
		get_locked_segment(addr);

	/* We are changing the virtual color of the page(s)
	 * so we must flush the cache to guarantee consistency.
	 */
	sun4c_flush_page(pages);
	sun4c_flush_page(pages + PAGE_SIZE);

	sun4c_put_pte(addr, BUCKET_PTE(pages));
	sun4c_put_pte(addr + PAGE_SIZE, BUCKET_PTE(pages + PAGE_SIZE));

#ifdef CONFIG_DEBUG_STACK_USAGE
	memset((void *)addr, 0, PAGE_SIZE << THREAD_INFO_ORDER);
#endif /* DEBUG_STACK_USAGE */

	return (struct thread_info *) addr;
}