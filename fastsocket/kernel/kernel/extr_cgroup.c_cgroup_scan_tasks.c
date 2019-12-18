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
struct timespec {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct task_struct {struct timespec start_time; } ;
struct ptr_heap {int size; struct task_struct** ptrs; int /*<<< orphan*/ * gt; } ;
struct cgroup_scanner {int /*<<< orphan*/  (* process_task ) (struct task_struct*,struct cgroup_scanner*) ;int /*<<< orphan*/  cg; int /*<<< orphan*/  (* test_task ) (struct task_struct*,struct cgroup_scanner*) ;struct ptr_heap* heap; } ;
struct cgroup_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  cgroup_iter_end (int /*<<< orphan*/ ,struct cgroup_iter*) ; 
 struct task_struct* cgroup_iter_next (int /*<<< orphan*/ ,struct cgroup_iter*) ; 
 int /*<<< orphan*/  cgroup_iter_start (int /*<<< orphan*/ ,struct cgroup_iter*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  heap_free (struct ptr_heap*) ; 
 int heap_init (struct ptr_heap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct task_struct* heap_insert (struct ptr_heap*,struct task_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  started_after ; 
 int /*<<< orphan*/  started_after_time (struct task_struct*,struct timespec*,struct task_struct*) ; 
 int /*<<< orphan*/  stub1 (struct task_struct*,struct cgroup_scanner*) ; 
 int /*<<< orphan*/  stub2 (struct task_struct*,struct cgroup_scanner*) ; 

int cgroup_scan_tasks(struct cgroup_scanner *scan)
{
	int retval, i;
	struct cgroup_iter it;
	struct task_struct *p, *dropped;
	/* Never dereference latest_task, since it's not refcounted */
	struct task_struct *latest_task = NULL;
	struct ptr_heap tmp_heap;
	struct ptr_heap *heap;
	struct timespec latest_time = { 0, 0 };

	if (scan->heap) {
		/* The caller supplied our heap and pre-allocated its memory */
		heap = scan->heap;
		heap->gt = &started_after;
	} else {
		/* We need to allocate our own heap memory */
		heap = &tmp_heap;
		retval = heap_init(heap, PAGE_SIZE, GFP_KERNEL, &started_after);
		if (retval)
			/* cannot allocate the heap */
			return retval;
	}

 again:
	/*
	 * Scan tasks in the cgroup, using the scanner's "test_task" callback
	 * to determine which are of interest, and using the scanner's
	 * "process_task" callback to process any of them that need an update.
	 * Since we don't want to hold any locks during the task updates,
	 * gather tasks to be processed in a heap structure.
	 * The heap is sorted by descending task start time.
	 * If the statically-sized heap fills up, we overflow tasks that
	 * started later, and in future iterations only consider tasks that
	 * started after the latest task in the previous pass. This
	 * guarantees forward progress and that we don't miss any tasks.
	 */
	heap->size = 0;
	cgroup_iter_start(scan->cg, &it);
	while ((p = cgroup_iter_next(scan->cg, &it))) {
		/*
		 * Only affect tasks that qualify per the caller's callback,
		 * if he provided one
		 */
		if (scan->test_task && !scan->test_task(p, scan))
			continue;
		/*
		 * Only process tasks that started after the last task
		 * we processed
		 */
		if (!started_after_time(p, &latest_time, latest_task))
			continue;
		dropped = heap_insert(heap, p);
		if (dropped == NULL) {
			/*
			 * The new task was inserted; the heap wasn't
			 * previously full
			 */
			get_task_struct(p);
		} else if (dropped != p) {
			/*
			 * The new task was inserted, and pushed out a
			 * different task
			 */
			get_task_struct(p);
			put_task_struct(dropped);
		}
		/*
		 * Else the new task was newer than anything already in
		 * the heap and wasn't inserted
		 */
	}
	cgroup_iter_end(scan->cg, &it);

	if (heap->size) {
		for (i = 0; i < heap->size; i++) {
			struct task_struct *q = heap->ptrs[i];
			if (i == 0) {
				latest_time = q->start_time;
				latest_task = q;
			}
			/* Process the task per the caller's callback */
			scan->process_task(q, scan);
			put_task_struct(q);
		}
		/*
		 * If we had to process any tasks at all, scan again
		 * in case some of them were in the middle of forking
		 * children that didn't get processed.
		 * Not the most efficient way to do it, but it avoids
		 * having to take callback_mutex in the fork path
		 */
		goto again;
	}
	if (heap == &tmp_heap)
		heap_free(&tmp_heap);
	return 0;
}