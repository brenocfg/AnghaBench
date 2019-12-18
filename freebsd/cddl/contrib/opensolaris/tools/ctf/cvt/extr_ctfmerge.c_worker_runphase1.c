#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int wq_nomorefiles; int wq_nwipslots; scalar_t__ wq_maxbatchsz; int /*<<< orphan*/  wq_queue_lock; TYPE_2__* wq_wip; int /*<<< orphan*/  wq_work_removed; int /*<<< orphan*/  wq_nextpownum; int /*<<< orphan*/  wq_queue; int /*<<< orphan*/  wq_work_avail; } ;
typedef  TYPE_1__ workqueue_t ;
struct TYPE_8__ {scalar_t__ wip_nmerged; int /*<<< orphan*/  wip_lock; } ;
typedef  TYPE_2__ wip_t ;
typedef  int /*<<< orphan*/  tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ fifo_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fifo_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wip_add_work (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wip_save_work (TYPE_1__*,TYPE_2__*,int) ; 

__attribute__((used)) static void
worker_runphase1(workqueue_t *wq)
{
	wip_t *wipslot;
	tdata_t *pow;
	int wipslotnum, pownum;

	for (;;) {
		pthread_mutex_lock(&wq->wq_queue_lock);

		while (fifo_empty(wq->wq_queue)) {
			if (wq->wq_nomorefiles == 1) {
				pthread_cond_broadcast(&wq->wq_work_avail);
				pthread_mutex_unlock(&wq->wq_queue_lock);

				/* on to phase 2 ... */
				return;
			}

			pthread_cond_wait(&wq->wq_work_avail,
			    &wq->wq_queue_lock);
		}

		/* there's work to be done! */
		pow = fifo_remove(wq->wq_queue);
		pownum = wq->wq_nextpownum++;
		pthread_cond_broadcast(&wq->wq_work_removed);

		assert(pow != NULL);

		/* merge it into the right slot */
		wipslotnum = pownum % wq->wq_nwipslots;
		wipslot = &wq->wq_wip[wipslotnum];

		pthread_mutex_lock(&wipslot->wip_lock);

		pthread_mutex_unlock(&wq->wq_queue_lock);

		wip_add_work(wipslot, pow);

		if (wipslot->wip_nmerged == wq->wq_maxbatchsz)
			wip_save_work(wq, wipslot, wipslotnum);

		pthread_mutex_unlock(&wipslot->wip_lock);
	}
}