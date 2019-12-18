#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* wq_ithrottle; int /*<<< orphan*/  wq_queue_lock; int /*<<< orphan*/  wq_work_avail; int /*<<< orphan*/  wq_queue; int /*<<< orphan*/  wq_work_removed; } ;
typedef  TYPE_1__ workqueue_t ;
typedef  int /*<<< orphan*/  tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,char*,...) ; 
 int /*<<< orphan*/  fifo_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* fifo_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 char* pthread_self () ; 

__attribute__((used)) static int
merge_ctf_cb(tdata_t *td, char *name, void *arg)
{
	workqueue_t *wq = arg;

	debug(3, "Adding tdata %p for processing\n", (void *)td);

	pthread_mutex_lock(&wq->wq_queue_lock);
	while (fifo_len(wq->wq_queue) > wq->wq_ithrottle) {
		debug(2, "Throttling input (len = %d, throttle = %d)\n",
		    fifo_len(wq->wq_queue), wq->wq_ithrottle);
		pthread_cond_wait(&wq->wq_work_removed, &wq->wq_queue_lock);
	}

	fifo_add(wq->wq_queue, td);
	debug(1, "Thread %d announcing %s\n", pthread_self(), name);
	pthread_cond_broadcast(&wq->wq_work_avail);
	pthread_mutex_unlock(&wq->wq_queue_lock);

	return (1);
}