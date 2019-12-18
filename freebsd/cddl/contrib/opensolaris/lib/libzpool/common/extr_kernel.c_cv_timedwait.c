#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/ * m_owner; int /*<<< orphan*/  m_lock; } ;
typedef  TYPE_1__ kmutex_t ;
typedef  int /*<<< orphan*/  kcondvar_t ;
typedef  int clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINTR ; 
 int ETIMEDOUT ; 
 int NANOSEC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * curthread ; 
 int ddi_get_lbolt () ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/ * mutex_owner (TYPE_1__*) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 

clock_t
cv_timedwait(kcondvar_t *cv, kmutex_t *mp, clock_t abstime)
{
	int error;
	struct timespec ts;
	struct timeval tv;
	clock_t delta;

	abstime += ddi_get_lbolt();
top:
	delta = abstime - ddi_get_lbolt();
	if (delta <= 0)
		return (-1);

	if (gettimeofday(&tv, NULL) != 0)
		assert(!"gettimeofday() failed");

	ts.tv_sec = tv.tv_sec + delta / hz;
	ts.tv_nsec = tv.tv_usec * 1000 + (delta % hz) * (NANOSEC / hz);
	ASSERT(ts.tv_nsec >= 0);

	if (ts.tv_nsec >= NANOSEC) {
		ts.tv_sec++;
		ts.tv_nsec -= NANOSEC;
	}

	ASSERT(mutex_owner(mp) == curthread);
	mp->m_owner = NULL;
	error = pthread_cond_timedwait(cv, &mp->m_lock, &ts);
	mp->m_owner = curthread;

	if (error == EINTR)
		goto top;

	if (error == ETIMEDOUT)
		return (-1);

	ASSERT(error == 0);

	return (1);
}