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
struct ipz_queue {int queue_length; int pagesize; scalar_t__* queue_pages; scalar_t__ small_page; } ;
struct ehca_pd {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGES_PER_KPAGE ; 
 int /*<<< orphan*/  ehca_gen_dbg (char*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_small_queue_page (struct ipz_queue*,struct ehca_pd*) ; 
 scalar_t__ is_vmalloc_addr (scalar_t__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  vfree (scalar_t__*) ; 

int ipz_queue_dtor(struct ehca_pd *pd, struct ipz_queue *queue)
{
	int i, nr_pages;

	if (!queue || !queue->queue_pages) {
		ehca_gen_dbg("queue or queue_pages is NULL");
		return 0;
	}

	if (queue->small_page)
		free_small_queue_page(queue, pd);
	else {
		nr_pages = queue->queue_length / queue->pagesize;
		for (i = 0; i < nr_pages; i += PAGES_PER_KPAGE)
			free_page((unsigned long)queue->queue_pages[i]);
	}

	if (is_vmalloc_addr(queue->queue_pages))
		vfree(queue->queue_pages);
	else
		kfree(queue->queue_pages);

	return 1;
}