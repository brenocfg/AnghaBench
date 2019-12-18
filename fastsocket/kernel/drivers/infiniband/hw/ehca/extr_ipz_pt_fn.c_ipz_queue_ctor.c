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
typedef  int u32 ;
struct ipz_queue {int queue_length; int pagesize; int qe_size; int act_nr_of_sg; int toggle_state; scalar_t__ queue_pages; int /*<<< orphan*/ * small_page; scalar_t__ current_q_offset; } ;
struct ehca_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int const PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_queue_pages (struct ipz_queue*,int const) ; 
 int /*<<< orphan*/  alloc_small_queue_page (struct ipz_queue*,struct ehca_pd*) ; 
 int /*<<< orphan*/  ehca_gen_err (char*,...) ; 
 scalar_t__ is_vmalloc_addr (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kzalloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 
 scalar_t__ vzalloc (int const) ; 

int ipz_queue_ctor(struct ehca_pd *pd, struct ipz_queue *queue,
		   const u32 nr_of_pages, const u32 pagesize,
		   const u32 qe_size, const u32 nr_of_sg,
		   int is_small)
{
	if (pagesize > PAGE_SIZE) {
		ehca_gen_err("FATAL ERROR: pagesize=%x "
			     "is greater than kernel page size", pagesize);
		return 0;
	}

	/* init queue fields */
	queue->queue_length = nr_of_pages * pagesize;
	queue->pagesize = pagesize;
	queue->qe_size = qe_size;
	queue->act_nr_of_sg = nr_of_sg;
	queue->current_q_offset = 0;
	queue->toggle_state = 1;
	queue->small_page = NULL;

	/* allocate queue page pointers */
	queue->queue_pages = kzalloc(nr_of_pages * sizeof(void *), GFP_KERNEL);
	if (!queue->queue_pages) {
		queue->queue_pages = vzalloc(nr_of_pages * sizeof(void *));
		if (!queue->queue_pages) {
			ehca_gen_err("Couldn't allocate queue page list");
			return 0;
		}
	}

	/* allocate actual queue pages */
	if (is_small) {
		if (!alloc_small_queue_page(queue, pd))
			goto ipz_queue_ctor_exit0;
	} else
		if (!alloc_queue_pages(queue, nr_of_pages))
			goto ipz_queue_ctor_exit0;

	return 1;

ipz_queue_ctor_exit0:
	ehca_gen_err("Couldn't alloc pages queue=%p "
		 "nr_of_pages=%x",  queue, nr_of_pages);
	if (is_vmalloc_addr(queue->queue_pages))
		vfree(queue->queue_pages);
	else
		kfree(queue->queue_pages);

	return 0;
}