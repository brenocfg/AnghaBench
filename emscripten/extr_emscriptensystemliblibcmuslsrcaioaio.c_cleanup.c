#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sigevent {scalar_t__ sigev_notify; int /*<<< orphan*/  sigev_value; int /*<<< orphan*/  (* sigev_notify_function ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  sigev_signo; } ;
struct aiocb {int /*<<< orphan*/  __err; int /*<<< orphan*/  __ret; struct sigevent aio_sigevent; } ;
struct aio_thread {TYPE_2__* next; TYPE_1__* prev; int /*<<< orphan*/  err; int /*<<< orphan*/  running; int /*<<< orphan*/  ret; struct aiocb* cb; struct aio_queue* q; } ;
struct aio_queue {int /*<<< orphan*/  cond; TYPE_2__* head; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  si_signo; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_value; } ;
typedef  TYPE_3__ siginfo_t ;
struct TYPE_9__ {int /*<<< orphan*/  cancel; } ;
struct TYPE_7__ {TYPE_1__* prev; } ;
struct TYPE_6__ {TYPE_2__* next; } ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 scalar_t__ SIGEV_SIGNAL ; 
 scalar_t__ SIGEV_THREAD ; 
 int /*<<< orphan*/  SI_ASYNCIO ; 
 int /*<<< orphan*/  SYS_rt_sigqueueinfo ; 
 int /*<<< orphan*/  __aio_fut ; 
 int /*<<< orphan*/  __aio_unref_queue (struct aio_queue*) ; 
 TYPE_5__* __pthread_self () ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  __wake (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  a_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ a_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup(void *ctx)
{
	struct aio_thread *at = ctx;
	struct aio_queue *q = at->q;
	struct aiocb *cb = at->cb;
	struct sigevent sev = cb->aio_sigevent;

	/* There are four potential types of waiters we could need to wake:
	 *   1. Callers of aio_cancel/close.
	 *   2. Callers of aio_suspend with a single aiocb.
	 *   3. Callers of aio_suspend with a list.
	 *   4. AIO worker threads waiting for sequenced operations.
	 * Types 1-3 are notified via atomics/futexes, mainly for AS-safety
	 * considerations. Type 4 is notified later via a cond var. */

	cb->__ret = at->ret;
	if (a_swap(&at->running, 0) < 0)
		__wake(&at->running, -1, 1);
	if (a_swap(&cb->__err, at->err) != EINPROGRESS)
		__wake(&cb->__err, -1, 1);
	if (a_swap(&__aio_fut, 0))
		__wake(&__aio_fut, -1, 1);

	pthread_mutex_lock(&q->lock);

	if (at->next) at->next->prev = at->prev;
	if (at->prev) at->prev->next = at->next;
	else q->head = at->next;

	/* Signal aio worker threads waiting for sequenced operations. */
	pthread_cond_broadcast(&q->cond);

	__aio_unref_queue(q);

	if (sev.sigev_notify == SIGEV_SIGNAL) {
		siginfo_t si = {
			.si_signo = sev.sigev_signo,
			.si_value = sev.sigev_value,
			.si_code = SI_ASYNCIO,
			.si_pid = getpid(),
			.si_uid = getuid()
		};
		__syscall(SYS_rt_sigqueueinfo, si.si_pid, si.si_signo, &si);
	}
	if (sev.sigev_notify == SIGEV_THREAD) {
		a_store(&__pthread_self()->cancel, 0);
		sev.sigev_notify_function(sev.sigev_value);
	}
}