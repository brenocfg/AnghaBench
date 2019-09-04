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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  __pthread_setcancelstate (int,int*) ; 
 int __timedwait_cp (int volatile*,int,int /*<<< orphan*/ ,struct timespec const*,int) ; 

int __timedwait(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{
	int cs, r;
	__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
#ifdef __EMSCRIPTEN__
	emscripten_conditional_set_current_thread_status(EM_THREAD_STATUS_RUNNING, EM_THREAD_STATUS_WAITMUTEX);
#endif
	r = __timedwait_cp(addr, val, clk, at, priv);
#ifdef __EMSCRIPTEN__
	emscripten_conditional_set_current_thread_status(EM_THREAD_STATUS_WAITMUTEX, EM_THREAD_STATUS_RUNNING);
#endif
	__pthread_setcancelstate(cs, 0);

	return r;
}