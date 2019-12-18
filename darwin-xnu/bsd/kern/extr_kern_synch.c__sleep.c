#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  scalar_t__ thread_continue_t ;
struct uthread {char const* uu_wmesg; int (* uu_continuation ) (int) ;int uu_pri; int uu_timo; int uu_flag; int /*<<< orphan*/ * uu_wchan; int /*<<< orphan*/ * uu_mtx; } ;
struct proc {int p_priority; TYPE_3__* p_sigacts; TYPE_2__* p_stats; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_6__ {int ps_sigintr; } ;
struct TYPE_4__ {int /*<<< orphan*/  ru_nvcsw; } ;
struct TYPE_5__ {TYPE_1__ p_ru; } ;

/* Variables and functions */
 int CURSIG (struct proc*) ; 
 int EINTR ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 scalar_t__ KERN_FAILURE ; 
 int LCK_SLEEP_DEFAULT ; 
 int LCK_SLEEP_SPIN ; 
 int LCK_SLEEP_UNLOCK ; 
 int /*<<< orphan*/  OSIncrementAtomicLong (int /*<<< orphan*/ *) ; 
 int PCATCH ; 
 int PDROP ; 
 int PRIMASK ; 
 int PSPIN ; 
 scalar_t__ SHOULDissignal (struct proc*,struct uthread*) ; 
 int THREAD_ABORTSAFE ; 
#define  THREAD_AWAKENED 131 
 scalar_t__ THREAD_CONTINUE_NULL ; 
#define  THREAD_INTERRUPTED 130 
#define  THREAD_RESTART 129 
#define  THREAD_TIMED_OUT 128 
 int THREAD_UNINT ; 
 int UT_CANCEL ; 
 int UT_CANCELDISABLE ; 
 int UT_CANCELED ; 
 scalar_t__ _sleep_continue ; 
 int /*<<< orphan*/  act_set_astbsd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_wait_deadline (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ clear_wait (int /*<<< orphan*/ ,int) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int lck_mtx_sleep (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int lck_mtx_sleep_deadline (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int sigmask (int) ; 
 int thread_block (scalar_t__) ; 
 scalar_t__ thread_should_abort (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_sleep(
	caddr_t		chan,
	int		pri,
	const char	*wmsg,
	u_int64_t	abstime,
	int		(*continuation)(int),
        lck_mtx_t	*mtx)
{
	struct proc *p;
	thread_t self = current_thread();
	struct uthread * ut;
	int sig, catch;
	int dropmutex  = pri & PDROP;
	int spinmutex  = pri & PSPIN;
	int wait_result;
	int error = 0;

	ut = get_bsdthread_info(self);

	p = current_proc();
	p->p_priority = pri & PRIMASK;
	/* It can still block in proc_exit() after the teardown. */
	if (p->p_stats != NULL)
		OSIncrementAtomicLong(&p->p_stats->p_ru.ru_nvcsw);
	
	if (pri & PCATCH)
		catch = THREAD_ABORTSAFE;
	else
		catch = THREAD_UNINT;

	/* set wait message & channel */
	ut->uu_wchan = chan;
	ut->uu_wmesg = wmsg ? wmsg : "unknown";

	if (mtx != NULL && chan != NULL && (thread_continue_t)continuation == THREAD_CONTINUE_NULL) {
		int	flags;

		if (dropmutex)
			flags = LCK_SLEEP_UNLOCK;
		else
			flags = LCK_SLEEP_DEFAULT;

		if (spinmutex)
			flags |= LCK_SLEEP_SPIN;

		if (abstime)
			wait_result = lck_mtx_sleep_deadline(mtx, flags, chan, catch, abstime);
		else
			wait_result = lck_mtx_sleep(mtx, flags, chan, catch);
	}
	else {
		if (chan != NULL)
			assert_wait_deadline(chan, catch, abstime);
		if (mtx)
			lck_mtx_unlock(mtx);

		if (catch == THREAD_ABORTSAFE) {
			if (SHOULDissignal(p,ut)) {
				if ((sig = CURSIG(p)) != 0) {
					if (clear_wait(self, THREAD_INTERRUPTED) == KERN_FAILURE)
						goto block;
					if (p->p_sigacts->ps_sigintr & sigmask(sig))
						error = EINTR;
					else
						error = ERESTART;
					if (mtx && !dropmutex) {
						if (spinmutex)
							lck_mtx_lock_spin(mtx);
						else
							lck_mtx_lock(mtx);
					}
					goto out;
				}
			}
			if (thread_should_abort(self)) {
				if (clear_wait(self, THREAD_INTERRUPTED) == KERN_FAILURE)
					goto block;
				error = EINTR;

				if (mtx && !dropmutex) {
					if (spinmutex)
						lck_mtx_lock_spin(mtx);
					else
						lck_mtx_lock(mtx);
				}
				goto out;
			}
		}		


block:
		if ((thread_continue_t)continuation != THREAD_CONTINUE_NULL) {
		        ut->uu_continuation = continuation;
			ut->uu_pri  = pri;
			ut->uu_timo = abstime? 1: 0;
			ut->uu_mtx  = mtx;
			(void) thread_block(_sleep_continue);
			/* NOTREACHED */
		}
		
		wait_result = thread_block(THREAD_CONTINUE_NULL);

		if (mtx && !dropmutex) {
			if (spinmutex)
				lck_mtx_lock_spin(mtx);
			else
				lck_mtx_lock(mtx);
		}
	}

	switch (wait_result) {
		case THREAD_TIMED_OUT:
			error = EWOULDBLOCK;
			break;
		case THREAD_AWAKENED:
		case THREAD_RESTART:
			/*
			 * Posix implies any signal should be delivered
			 * first, regardless of whether awakened due
			 * to receiving event.
			 */
			if (catch != THREAD_ABORTSAFE)
				break;
			/* else fall through */
		case THREAD_INTERRUPTED:
			if (catch == THREAD_ABORTSAFE) {
				if (thread_should_abort(self)) {
					error = EINTR;
				} else if (SHOULDissignal(p, ut)) {
					if ((sig = CURSIG(p)) != 0) {
						if (p->p_sigacts->ps_sigintr & sigmask(sig))
							error = EINTR;
						else
							error = ERESTART;
					}
					if (thread_should_abort(self)) {
						error = EINTR;
					}
				} else if( (ut->uu_flag & ( UT_CANCELDISABLE | UT_CANCEL | UT_CANCELED)) == UT_CANCEL) {
                                        /* due to thread cancel */
                                        error = EINTR;
                                }
			}  else
				error = EINTR;
			break;
	}
out:
	if (error == EINTR || error == ERESTART)
		act_set_astbsd(self);
	ut->uu_wchan = NULL;
	ut->uu_wmesg = NULL;

	return (error);
}