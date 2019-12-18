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
struct thread_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_EMPTY ; 
 int BUCKET_NUM (unsigned long) ; 
 unsigned long BUCKET_PTE_PAGE (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  THREAD_INFO_ORDER ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garbage_collect (int) ; 
 int /*<<< orphan*/ * sun4c_bucket ; 
 int /*<<< orphan*/  sun4c_flush_page (unsigned long) ; 
 int /*<<< orphan*/  sun4c_get_pte (unsigned long) ; 
 int sun4c_lowbucket_avail ; 
 int /*<<< orphan*/  sun4c_put_pte (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4c_free_thread_info(struct thread_info *ti)
{
	unsigned long tiaddr = (unsigned long) ti;
	unsigned long pages = BUCKET_PTE_PAGE(sun4c_get_pte(tiaddr));
	int entry = BUCKET_NUM(tiaddr);

	/* We are deleting a mapping, so the flush here is mandatory. */
	sun4c_flush_page(tiaddr);
	sun4c_flush_page(tiaddr + PAGE_SIZE);

	sun4c_put_pte(tiaddr, 0);
	sun4c_put_pte(tiaddr + PAGE_SIZE, 0);

	sun4c_bucket[entry] = BUCKET_EMPTY;
	if (entry < sun4c_lowbucket_avail)
		sun4c_lowbucket_avail = entry;

	free_pages(pages, THREAD_INFO_ORDER);
	garbage_collect(entry);
}