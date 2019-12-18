#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  wq_bar2; int /*<<< orphan*/  wq_queue; int /*<<< orphan*/  wq_ninqueue; int /*<<< orphan*/  wq_bar1; } ;
typedef  TYPE_1__ workqueue_t ;

/* Variables and functions */
 scalar_t__ barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fifo_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_phase_one (TYPE_1__*) ; 
 int /*<<< orphan*/  init_phase_two (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  worker_runphase1 (TYPE_1__*) ; 
 int /*<<< orphan*/  worker_runphase2 (TYPE_1__*) ; 

__attribute__((used)) static void
worker_thread(workqueue_t *wq)
{
	worker_runphase1(wq);

	debug(2, "%d: entering first barrier\n", pthread_self());

	if (barrier_wait(&wq->wq_bar1)) {

		debug(2, "%d: doing work in first barrier\n", pthread_self());

		finalize_phase_one(wq);

		init_phase_two(wq);

		debug(2, "%d: ninqueue is %d, %d on queue\n", pthread_self(),
		    wq->wq_ninqueue, fifo_len(wq->wq_queue));
	}

	debug(2, "%d: entering second barrier\n", pthread_self());

	(void) barrier_wait(&wq->wq_bar2);

	debug(2, "%d: phase 1 complete\n", pthread_self());

	worker_runphase2(wq);
}