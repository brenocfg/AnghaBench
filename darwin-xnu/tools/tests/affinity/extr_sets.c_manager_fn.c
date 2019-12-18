#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ work_t ;
typedef  int /*<<< orphan*/  thread_policy_t ;
struct TYPE_14__ {void* timeshare; } ;
typedef  TYPE_4__ thread_extended_policy_data_t ;
struct TYPE_15__ {int /*<<< orphan*/  affinity_tag; } ;
typedef  TYPE_5__ thread_affinity_policy_data_t ;
struct TYPE_16__ {int /*<<< orphan*/  stagenum; int /*<<< orphan*/  name; TYPE_2__* output; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* input; TYPE_7__* set; } ;
typedef  TYPE_6__ stage_info_t ;
struct TYPE_17__ {int /*<<< orphan*/  setnum; int /*<<< orphan*/  isize; } ;
typedef  TYPE_7__ line_info_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_12__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  cnd; scalar_t__ waiters; int /*<<< orphan*/  queue; } ;
struct TYPE_11__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  queue; void* waiters; int /*<<< orphan*/  cnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 void* FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_3__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY ; 
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY_COUNT ; 
 int /*<<< orphan*/  THREAD_EXTENDED_POLICY ; 
 int /*<<< orphan*/  THREAD_EXTENDED_POLICY_COUNT ; 
 void* TRUE ; 
 scalar_t__ affinity ; 
 int /*<<< orphan*/  barrier ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funnel ; 
 int /*<<< orphan*/  getchar () ; 
 int getpid () ; 
 scalar_t__ halting ; 
 long iterations ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  mach_thread_self () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_policy_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ threads ; 
 scalar_t__ threads_ready ; 
 int /*<<< orphan*/  timer ; 

void *
manager_fn(void *arg)
{
	stage_info_t			*sp = (stage_info_t *) arg;
	line_info_t			*lp = sp->set;
	kern_return_t			ret;
	long				iteration = 0;

	/*
	 * If we're using affinity sets (we are by default)
	 * set our tag to by our thread set number.
	 */
	thread_extended_policy_data_t	epolicy;
	thread_affinity_policy_data_t	policy;

	epolicy.timeshare = FALSE;
	ret = thread_policy_set(
			mach_thread_self(), THREAD_EXTENDED_POLICY,
			(thread_policy_t) &epolicy,
			THREAD_EXTENDED_POLICY_COUNT);
	if (ret != KERN_SUCCESS)
		printf("thread_policy_set(THREAD_EXTENDED_POLICY) returned %d\n", ret);
	
	if (affinity) {
		policy.affinity_tag = lp->setnum;
		ret = thread_policy_set(
				mach_thread_self(), THREAD_AFFINITY_POLICY,
				(thread_policy_t) &policy,
				THREAD_AFFINITY_POLICY_COUNT);
		if (ret != KERN_SUCCESS)
			printf("thread_policy_set(THREAD_AFFINITY_POLICY) returned %d\n", ret);
	}

	DBG("Starting %s set: %d stage: %d\n", sp->name, lp->setnum, sp->stagenum);

	/*
	 * Start barrier.
	 * The tets thread to get here releases everyone and starts the timer.
	 */
	pthread_mutex_lock(&funnel);
	threads_ready++;
	if (threads_ready == threads) {
		pthread_mutex_unlock(&funnel);
		if (halting) {
			printf("  all threads ready for process %d, "
				"hit any key to start", getpid());
			fflush(stdout);
			(void) getchar();
		}
		pthread_cond_broadcast(&barrier);
		timer = mach_absolute_time();
	} else {
		pthread_cond_wait(&barrier, &funnel);
		pthread_mutex_unlock(&funnel);
	}

	do {
		int		i;
		work_t		*workp;

		/*
		 * Get a buffer from the input queue.
		 * Block if none.
		 */
		pthread_mutex_lock(&sp->input->mtx);
		while (1) {
			workp = TAILQ_FIRST(&(sp->input->queue));
			if (workp != NULL)
				break;
			DBG("    %s[%d,%d] iteration %d waiting for buffer\n",
				sp->name, lp->setnum, sp->stagenum, iteration);
			sp->input->waiters = TRUE;
			pthread_cond_wait(&sp->input->cnd, &sp->input->mtx);
			sp->input->waiters = FALSE;
		}
		TAILQ_REMOVE(&(sp->input->queue), workp, link);
		pthread_mutex_unlock(&sp->input->mtx);

		DBG("  %s[%d,%d] iteration %d work %p data %p\n",
			sp->name, lp->setnum, sp->stagenum, iteration, workp, workp->data);

		/* Do our stuff with the buffer */
		(void) sp->fn(workp->data, lp->isize);

		/*
		 * Place the buffer on the input queue.
		 * Signal  waiters if required.
		 */
		pthread_mutex_lock(&sp->output->mtx);
		TAILQ_INSERT_TAIL(&(sp->output->queue), workp, link);
		if (sp->output->waiters) {
			DBG("    %s[%d,%d] iteration %d signaling work\n",
				sp->name, lp->setnum, sp->stagenum, iteration);
			pthread_cond_signal(&sp->output->cnd);
		}
		pthread_mutex_unlock(&sp->output->mtx);
	} while (++iteration < iterations);

	DBG("Ending %s[%d,%d]\n", sp->name, lp->setnum, sp->stagenum);

	return (void *) iteration;
}