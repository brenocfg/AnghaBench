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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
struct TYPE_4__ {scalar_t__ lock; struct TYPE_4__* postponed_next; } ;
typedef  TYPE_1__ malloc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeCriticalSectionAndSpinCount (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeSRWLock (scalar_t__*) ; 
 int /*<<< orphan*/  MALLOC_MUTEX_TYPE ; 
 int /*<<< orphan*/  _CRT_SPINCOUNT ; 
 scalar_t__ _pthread_mutex_init_calloc_cb (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootstrap_calloc ; 
 scalar_t__ postpone_init ; 
 TYPE_1__* postponed_mutexes ; 
 scalar_t__ pthread_mutex_init (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
malloc_mutex_init(malloc_mutex_t *mutex)
{

#ifdef _WIN32
#  if _WIN32_WINNT >= 0x0600
	InitializeSRWLock(&mutex->lock);
#  else
	if (!InitializeCriticalSectionAndSpinCount(&mutex->lock,
	    _CRT_SPINCOUNT))
		return (true);
#  endif
#elif (defined(JEMALLOC_OSSPIN))
	mutex->lock = 0;
#elif (defined(JEMALLOC_MUTEX_INIT_CB))
	if (postpone_init) {
		mutex->postponed_next = postponed_mutexes;
		postponed_mutexes = mutex;
	} else {
		if (_pthread_mutex_init_calloc_cb(&mutex->lock,
		    bootstrap_calloc) != 0)
			return (true);
	}
#else
	pthread_mutexattr_t attr;

	if (pthread_mutexattr_init(&attr) != 0)
		return (true);
	pthread_mutexattr_settype(&attr, MALLOC_MUTEX_TYPE);
	if (pthread_mutex_init(&mutex->lock, &attr) != 0) {
		pthread_mutexattr_destroy(&attr);
		return (true);
	}
	pthread_mutexattr_destroy(&attr);
#endif
	return (false);
}