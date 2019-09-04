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
struct fileproc {int f_flags; void* f_wset; } ;

/* Variables and functions */
 int FP_INSELECT ; 
 int FP_SELCONFLICT ; 
 int /*<<< orphan*/  select_conflict_queue ; 
 int waitq_set_is_valid (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlink (int /*<<< orphan*/ *,struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlink_by_prepost_id (int /*<<< orphan*/ ,struct waitq_set*) ; 

__attribute__((used)) static void selunlinkfp(struct fileproc *fp, uint64_t wqp_id, struct waitq_set *wqset)
{
	int valid_set = waitq_set_is_valid(wqset);
	int valid_q = !!wqp_id;

	/*
	 * This could be called (from selcount error path) before we setup
	 * the thread's wqset. Check the wqset passed in, and only unlink if
	 * the set is valid.
	 */

	/* unlink the underlying waitq from the input set (thread waitq set) */
	if (valid_q && valid_set)
		waitq_unlink_by_prepost_id(wqp_id, wqset);

	/* allow passing a NULL/invalid fp for seldrop unwind */
	if (!fp || !(fp->f_flags & (FP_INSELECT|FP_SELCONFLICT)))
		return;

	/*
	 * We can always remove the conflict queue from our thread's set: this
	 * will not affect other threads that potentially need to be awoken on
	 * the conflict queue during a fileproc_drain - those sets will still
	 * be linked with the global conflict queue, and the last waiter
	 * on the fp clears the CONFLICT marker.
	 */
	if (valid_set && (fp->f_flags & FP_SELCONFLICT))
		waitq_unlink(&select_conflict_queue, wqset);

	/* jca: TODO:
	 * This isn't quite right - we don't actually know if this
	 * fileproc is in another select or not! Here we just assume
	 * that if we were the first thread to select on the FD, then
	 * we'll be the one to clear this flag...
	 */
	if (valid_set && fp->f_wset == (void *)wqset) {
		fp->f_flags &= ~FP_INSELECT;
		fp->f_wset = NULL;
	}
}