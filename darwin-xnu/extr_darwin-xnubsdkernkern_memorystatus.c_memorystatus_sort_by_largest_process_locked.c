#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_12__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ memstat_bucket_t ;
struct TYPE_11__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 unsigned int MEMSTAT_BUCKET_COUNT ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memorystatus_get_task_page_counts (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* memstat_bucket ; 
 int /*<<< orphan*/  p_memstat_list ; 

__attribute__((used)) static void memorystatus_sort_by_largest_process_locked(unsigned int bucket_index)
{
	proc_t p = NULL, insert_after_proc = NULL, max_proc = NULL;
	proc_t next_p = NULL, prev_max_proc = NULL;
	uint32_t pages = 0, max_pages = 0;
	memstat_bucket_t *current_bucket;
		
	if (bucket_index >= MEMSTAT_BUCKET_COUNT) {
		return;
	}
		
	current_bucket = &memstat_bucket[bucket_index];

	p = TAILQ_FIRST(&current_bucket->list);

	while (p) {
		memorystatus_get_task_page_counts(p->task, &pages, NULL, NULL);
		max_pages = pages;
		max_proc = p;
		prev_max_proc = p;
		
		while ((next_p = TAILQ_NEXT(p, p_memstat_list)) != NULL) {
			/* traversing list until we find next largest process */
			p=next_p;
			memorystatus_get_task_page_counts(p->task, &pages, NULL, NULL);
			if (pages > max_pages) {
				max_pages = pages;
				max_proc = p;
			}
		}

		if (prev_max_proc != max_proc) {
			/* found a larger process, place it in the list */
			TAILQ_REMOVE(&current_bucket->list, max_proc, p_memstat_list);
			if (insert_after_proc == NULL) {
				TAILQ_INSERT_HEAD(&current_bucket->list, max_proc, p_memstat_list);
			} else {
				TAILQ_INSERT_AFTER(&current_bucket->list, insert_after_proc, max_proc, p_memstat_list);
			}
			prev_max_proc = max_proc;
		}

		insert_after_proc = max_proc;

		p = TAILQ_NEXT(max_proc, p_memstat_list);
	}
}