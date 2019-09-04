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
struct timespec {unsigned long tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int ECANCELED ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOSYS ; 
 int ETIMEDOUT ; 
 int FUTEX_WAIT ; 
 int /*<<< orphan*/  SYS_futex ; 
 scalar_t__ __clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int __syscall_cp (int /*<<< orphan*/ ,int volatile*,int,int,struct timespec*) ; 

int __timedwait_cp(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{
	int r;
	struct timespec to, *top=0;

	if (priv) priv = 128;

	if (at) {
		if (at->tv_nsec >= 1000000000UL) return EINVAL;
		if (__clock_gettime(clk, &to)) return EINVAL;
		to.tv_sec = at->tv_sec - to.tv_sec;
		if ((to.tv_nsec = at->tv_nsec - to.tv_nsec) < 0) {
			to.tv_sec--;
			to.tv_nsec += 1000000000;
		}
		if (to.tv_sec < 0) return ETIMEDOUT;
		top = &to;
	}

#ifdef __EMSCRIPTEN__
	double msecsToSleep = top ? (top->tv_sec * 1000 + top->tv_nsec / 1000000.0) : INFINITY;
	int is_main_thread = emscripten_is_main_browser_thread();
	if (is_main_thread || pthread_self()->cancelasync == PTHREAD_CANCEL_ASYNCHRONOUS) {
		double sleepUntilTime = emscripten_get_now() + msecsToSleep;
		do {
			if (_pthread_isduecanceled(pthread_self())) {
				// Emscripten-specific return value: The wait was canceled by user calling
				// pthread_cancel() for this thread, and the caller needs to cooperatively
				// cancel execution.
				return ECANCELED;
			}
			// Assist other threads by executing proxied operations that are effectively singlethreaded.
			if (is_main_thread) emscripten_main_thread_process_queued_calls();
			// Must wait in slices in case this thread is cancelled in between.
			double waitMsecs = sleepUntilTime - emscripten_get_now();
			if (waitMsecs <= 0) {
				r = ETIMEDOUT;
				break;
			}
			if (waitMsecs > 100) waitMsecs = 100; // non-main threads can sleep in longer slices.
			if (is_main_thread && waitMsecs > 1) waitMsecs = 1; // main thread may need to run proxied calls, so sleep in very small slices to be responsive.
			r = -emscripten_futex_wait((void*)addr, val, waitMsecs);
		} while(r == ETIMEDOUT);
	} else {
		// Can wait in one go.
		r = -emscripten_futex_wait((void*)addr, val, msecsToSleep);
	}
#else
	r = -__syscall_cp(SYS_futex, addr, FUTEX_WAIT|priv, val, top);
	if (r == ENOSYS) r = -__syscall_cp(SYS_futex, addr, FUTEX_WAIT, val, top);
#endif
	if (r != EINTR && r != ETIMEDOUT && r != ECANCELED) r = 0;

	return r;
}