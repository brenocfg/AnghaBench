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
typedef  int /*<<< orphan*/  uint64_t ;
struct waitq_set {int dummy; } ;
struct waitq {int dummy; } ;
struct fileproc {int f_flags; void* f_wset; } ;
typedef  int /*<<< orphan*/  f_wq ;

/* Variables and functions */
 int FP_INSELECT ; 
 int FP_SELCONFLICT ; 
 int /*<<< orphan*/  WAITQ_SHOULD_LOCK ; 
 int /*<<< orphan*/  memcpy (struct waitq**,void**,int) ; 
 int /*<<< orphan*/  panic (char*,void**,struct fileproc*,struct waitq_set*) ; 
 int /*<<< orphan*/  select_conflict_queue ; 
 int /*<<< orphan*/  waitq_get_prepost_id (struct waitq*) ; 
 int /*<<< orphan*/  waitq_is_valid (struct waitq*) ; 
 int /*<<< orphan*/  waitq_link (int /*<<< orphan*/ *,struct waitq_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t sellinkfp(struct fileproc *fp, void **wq_data, struct waitq_set *wqset)
{
	struct waitq *f_wq = NULL;

	if ((fp->f_flags & FP_INSELECT) != FP_INSELECT) {
		if (wq_data)
			panic("non-null data:%p on fp:%p not in select?!"
			      "(wqset:%p)", wq_data, fp, wqset);
		return 0;
	}

	if ((fp->f_flags & FP_SELCONFLICT) == FP_SELCONFLICT) {
		waitq_link(&select_conflict_queue, wqset, WAITQ_SHOULD_LOCK, NULL);
	}

	/*
	 * The wq_data parameter has potentially been set by selrecord called
	 * from a subsystems fo_select() function. If the subsystem does not
	 * call selrecord, then wq_data will be NULL
	 *
	 * Use memcpy to get the value into a proper pointer because
	 * wq_data most likely points to a stack variable that could be
	 * unaligned on 32-bit systems.
	 */
	if (wq_data) {
		memcpy(&f_wq, wq_data, sizeof(f_wq));
		if (!waitq_is_valid(f_wq))
			f_wq = NULL;
	}

	/* record the first thread's wqset in the fileproc structure */
	if (!fp->f_wset)
		fp->f_wset = (void *)wqset;

	/* handles NULL f_wq */
	return waitq_get_prepost_id(f_wq);
}