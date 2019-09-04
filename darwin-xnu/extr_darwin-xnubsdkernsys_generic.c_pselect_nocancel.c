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
typedef  int /*<<< orphan*/  ts64 ;
typedef  int /*<<< orphan*/  ts32 ;
struct uthread {int uu_oldmask; int uu_sigmask; int uu_flag; } ;
struct user64_timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct user32_timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct select_nocancel_args {int dummy; } ;
struct pselect_nocancel_args {scalar_t__ ts; scalar_t__ mask; } ;
struct proc {int dummy; } ;
typedef  int sigset_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int* caddr_t ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 scalar_t__ USER_ADDR_NULL ; 
 int UT_SAS_OLDMASK ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int copyin (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int select_internal (struct proc*,struct select_nocancel_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sigcantmask ; 
 int /*<<< orphan*/  timespec_is_valid (struct timespec*) ; 
 int /*<<< orphan*/  tstoabstime (struct timespec*) ; 

int
pselect_nocancel(struct proc *p, struct pselect_nocancel_args *uap, int32_t *retval)
{
	int err;
	struct uthread *ut;
	uint64_t timeout = 0;

	if (uap->ts) {
		struct timespec ts;

		if (IS_64BIT_PROCESS(p)) {
			struct user64_timespec ts64;
			err = copyin(uap->ts, (caddr_t)&ts64, sizeof(ts64));
			ts.tv_sec = ts64.tv_sec;
			ts.tv_nsec = ts64.tv_nsec;
		} else {
			struct user32_timespec ts32;
			err = copyin(uap->ts, (caddr_t)&ts32, sizeof(ts32));
			ts.tv_sec = ts32.tv_sec;
			ts.tv_nsec = ts32.tv_nsec;
		}
		if (err) {
			return err;
		}

		if (!timespec_is_valid(&ts)) {
			return EINVAL;
		}
		clock_absolutetime_interval_to_deadline(tstoabstime(&ts), &timeout);
	}

	ut = get_bsdthread_info(current_thread());

	if (uap->mask != USER_ADDR_NULL) {
		/* save current mask, then copyin and set new mask */
		sigset_t newset;
		err = copyin(uap->mask, &newset, sizeof(sigset_t));
		if (err) {
			return err;
		}
		ut->uu_oldmask = ut->uu_sigmask;
		ut->uu_flag |= UT_SAS_OLDMASK;
		ut->uu_sigmask = (newset & ~sigcantmask);
	}

	err = select_internal(p, (struct select_nocancel_args *)uap, timeout, retval);

	if (err != EINTR && ut->uu_flag & UT_SAS_OLDMASK) {
		/*
		 * Restore old mask (direct return case). NOTE: EINTR can also be returned
		 * if the thread is cancelled. In that case, we don't reset the signal
		 * mask to its original value (which usually happens in the signal
		 * delivery path). This behavior is permitted by POSIX.
		 */
		ut->uu_sigmask = ut->uu_oldmask;
		ut->uu_oldmask = 0;
		ut->uu_flag &= ~UT_SAS_OLDMASK;
	}

	return err;
}