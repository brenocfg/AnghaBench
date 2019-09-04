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
typedef  int /*<<< orphan*/  waitq_select_cb ;
typedef  int /*<<< orphan*/  uint64_t ;
struct waitq_select_args {void* select_ctx; int max_threads; int* nthreads; int /*<<< orphan*/ * spl; int /*<<< orphan*/  threadq; int /*<<< orphan*/ * reserved_preposts; int /*<<< orphan*/  select_cb; int /*<<< orphan*/  event; struct waitq* waitq; struct waitq* posted_waitq; } ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  queue_t ;
typedef  int /*<<< orphan*/  event64_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_waitq_select_n_locked (struct waitq_select_args*) ; 

__attribute__((used)) static __inline__ int waitq_select_n_locked(struct waitq *waitq,
					    event64_t event,
					    waitq_select_cb select_cb,
					    void *select_ctx,
					    uint64_t *reserved_preposts,
					    queue_t threadq,
					    int max_threads, spl_t *spl)
{
	int nthreads = 0;

	struct waitq_select_args args = {
		.posted_waitq = waitq,
		.waitq = waitq,
		.event = event,
		.select_cb = select_cb,
		.select_ctx = select_ctx,
		.reserved_preposts = reserved_preposts,
		.threadq = threadq,
		.max_threads = max_threads,
		.nthreads = &nthreads,
		.spl = spl,
	};

	do_waitq_select_n_locked(&args);
	return nthreads;
}