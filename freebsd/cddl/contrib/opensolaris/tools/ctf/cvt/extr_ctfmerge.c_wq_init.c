#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int wq_maxbatchsz; int wq_nwipslots; int wq_nthreads; int wq_ithrottle; int wq_ninqueue; int wq_lastdonebatch; scalar_t__ wq_nomorefiles; int /*<<< orphan*/  wq_bar2; int /*<<< orphan*/  wq_bar1; scalar_t__ wq_alldone; int /*<<< orphan*/  wq_alldone_cv; int /*<<< orphan*/  wq_done_cv; void* wq_donequeue; int /*<<< orphan*/  wq_donequeue_lock; scalar_t__ wq_nextpownum; int /*<<< orphan*/  wq_work_removed; int /*<<< orphan*/  wq_work_avail; void* wq_queue; int /*<<< orphan*/  wq_queue_lock; scalar_t__ wq_next_batchid; TYPE_2__* wq_wip; int /*<<< orphan*/  wq_thread; } ;
typedef  TYPE_1__ workqueue_t ;
typedef  int /*<<< orphan*/  wip_t ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_5__ {scalar_t__ wip_batchid; int /*<<< orphan*/  wip_lock; } ;

/* Variables and functions */
 int MERGE_INPUT_THROTTLE_LEN ; 
 int MERGE_PHASE1_BATCH_SIZE ; 
 int MERGE_PHASE1_MAX_SLOTS ; 
 void* MIN (int,int) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 void* atoi (scalar_t__) ; 
 int /*<<< orphan*/  barrier_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debug (int,char*,int,int) ; 
 void* fifo_new () ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 TYPE_2__* xcalloc (int) ; 
 int /*<<< orphan*/  xmalloc (int) ; 

__attribute__((used)) static void
wq_init(workqueue_t *wq, int nfiles)
{
	int throttle, nslots, i;

	if (getenv("CTFMERGE_MAX_SLOTS"))
		nslots = atoi(getenv("CTFMERGE_MAX_SLOTS"));
	else
		nslots = MERGE_PHASE1_MAX_SLOTS;

	if (getenv("CTFMERGE_PHASE1_BATCH_SIZE"))
		wq->wq_maxbatchsz = atoi(getenv("CTFMERGE_PHASE1_BATCH_SIZE"));
	else
		wq->wq_maxbatchsz = MERGE_PHASE1_BATCH_SIZE;

	nslots = MIN(nslots, (nfiles + wq->wq_maxbatchsz - 1) /
	    wq->wq_maxbatchsz);

	wq->wq_wip = xcalloc(sizeof (wip_t) * nslots);
	wq->wq_nwipslots = nslots;
	wq->wq_nthreads = MIN(sysconf(_SC_NPROCESSORS_ONLN) * 3 / 2, nslots);
	wq->wq_thread = xmalloc(sizeof (pthread_t) * wq->wq_nthreads);

	if (getenv("CTFMERGE_INPUT_THROTTLE"))
		throttle = atoi(getenv("CTFMERGE_INPUT_THROTTLE"));
	else
		throttle = MERGE_INPUT_THROTTLE_LEN;
	wq->wq_ithrottle = throttle * wq->wq_nthreads;

	debug(1, "Using %d slots, %d threads\n", wq->wq_nwipslots,
	    wq->wq_nthreads);

	wq->wq_next_batchid = 0;

	for (i = 0; i < nslots; i++) {
		pthread_mutex_init(&wq->wq_wip[i].wip_lock, NULL);
		wq->wq_wip[i].wip_batchid = wq->wq_next_batchid++;
	}

	pthread_mutex_init(&wq->wq_queue_lock, NULL);
	wq->wq_queue = fifo_new();
	pthread_cond_init(&wq->wq_work_avail, NULL);
	pthread_cond_init(&wq->wq_work_removed, NULL);
	wq->wq_ninqueue = nfiles;
	wq->wq_nextpownum = 0;

	pthread_mutex_init(&wq->wq_donequeue_lock, NULL);
	wq->wq_donequeue = fifo_new();
	wq->wq_lastdonebatch = -1;

	pthread_cond_init(&wq->wq_done_cv, NULL);

	pthread_cond_init(&wq->wq_alldone_cv, NULL);
	wq->wq_alldone = 0;

	barrier_init(&wq->wq_bar1, wq->wq_nthreads);
	barrier_init(&wq->wq_bar2, wq->wq_nthreads);

	wq->wq_nomorefiles = 0;
}